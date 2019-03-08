#include "benchmark.h"
#include "msa.h"
#include "partition.h"
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <utility>

#ifdef __linux__
#include <fstream>
#include <unistd.h>
#elif _WIN32
// nothing
#endif

namespace dks {
inline benchmark_time_t weight_kernel_times(kernel_weight_t kw,
                                            benchmark_result_t bmr) {
  return kw[test_kernel_t::partial] * bmr[test_kernel_t::partial] +
         kw[test_kernel_t::likelihood] * bmr[test_kernel_t::likelihood] +
         kw[test_kernel_t::derivative] * bmr[test_kernel_t::derivative] +
         kw[test_kernel_t::pmatrix] * bmr[test_kernel_t::pmatrix];
}

attributes_t select_kernel(const pll_partition_t *pll_partition,
                           const pll_msa_t *pll_msa,
                           const kernel_weight_t &kw) {
  msa_t msa{pll_msa};
  model_t model{pll_partition};
  return select_kernel(model, msa, kw);
}

attributes_time_t select_kernel_verbose(const model_t &model, const msa_t &msa,
                                        const kernel_weight_t &kw) {
  attributes_time_t times;
  msa_compressed_t cmsa(msa);
  double msa_entropy = cmsa.column_entropy();
  for (uint8_t bit_attribs = 0; bit_attribs < 0x8; ++bit_attribs) {
    for (uint8_t simd = test_cpu_t::none; simd <= test_cpu_t::avx2; ++simd) {
      if (static_cast<bool>(bit_attribs & (1 << 0)) &&
          static_cast<bool>(bit_attribs & (1 << 1))) {
        continue;
      }

      attributes_t attribs(static_cast<bool>(bit_attribs & (1 << 0)),
                           static_cast<bool>(bit_attribs & (1 << 1)),
                           static_cast<bool>(bit_attribs & (1 << 2)),
                           static_cast<test_cpu_t>(simd));
      test_case_t tc(attribs);
      times[attribs] = weight_kernel_times(kw, tc.benchmark(msa, model));
      if (attribs.site_repeats) {
        times[attribs] *= msa_entropy;
      }
    }
  }
  return times;
}

attributes_t select_kernel(const model_t &model, const msa_t &msa,
                           const kernel_weight_t &kw) {
  auto times = select_kernel_verbose(model, msa, kw);
  return std::max_element(times.begin(), times.end(),
                          [](const attributes_time_t::value_type &a,
                             const attributes_time_t::value_type &b) {
                            return a.second < b.second;
                          })
      ->first;
}

#ifdef __linux__
std::string build_path(size_t cpu_number) {
  std::string s;
  s += "/sys/devices/system/cpu/cpu";
  int leading_zeros = std::floor(std::log10(cpu_number));
  for (int i = 0; i < leading_zeros; ++i) {
    s += "0";
  }
  s += std::to_string(cpu_number);
  s += "/topology/core_id";
  return s;
}

size_t get_core_id(size_t cpu_number) {
  std::string filename = build_path(cpu_number);
  std::ifstream f(filename.c_str());
  char buf[32];
  f.getline(buf, 32);
  return std::stoi(buf);
}

int physical_cpu_count() {
  size_t cpu_max = 0;
  size_t n_cpu = sysconf(_SC_NPROCESSORS_ONLN);
  for (size_t i = 0; i < n_cpu; ++i) {
    size_t core_id = get_core_id(i);
    cpu_max = core_id > cpu_max ? core_id : cpu_max;
  }
  return cpu_max + 1;
}

#elif _WIN32
int physical_cpu_count() { return -1; }
#endif
} // namespace dks
