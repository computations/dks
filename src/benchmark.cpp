#include "benchmark.h"
#include "msa.h"
#include "partition.h"
#include <algorithm>
#include <unordered_map>
#include <utility>

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
} // namespace dks
