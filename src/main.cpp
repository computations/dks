#include "benchmark.h"
#include <algorithm>
#include <getopt.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <unistd.h>

using namespace std;

option cli_options[] = {
    {"msa", required_argument, 0, 0},
    {0, 0, 0, 0},
};

int main(int argc, char **argv) {
  int opt_index;
  string filename;
  char c;
  while ((c = getopt_long(argc, argv, "", cli_options, &opt_index)) == 0) {
    switch (opt_index) {
    case 0:
      filename = string(optarg);
      break;
    }
  }
  if (filename.empty()) {
    cout << "Please give an msa file with the --msa switch" << endl;
    return 1;
  }

  dks::msa_t msa(filename);
  dks::model_t model(msa);
  dks::kernel_weight_t kw{
      {dks::test_kernel_t::likelihood, 1.0 / 4.0},
      {dks::test_kernel_t::partial, 1.0 / 4.0},
      {dks::test_kernel_t::derivative, 1 / 8.0},
      {dks::test_kernel_t::pmatrix, 1 / 8.0},
  };

  auto results = dks::select_kernel_verbose(model, msa, kw);

  vector<pair<dks::attributes_t, dks::benchmark_time_t>> sorted_times{
      results.begin(), results.end()};
  std::sort(sorted_times.begin(), sorted_times.end(),
            [](const decltype(sorted_times)::value_type &a,
               const decltype(sorted_times)::value_type &b) {
              return a.second < b.second;
            });

  for (const auto &kv : sorted_times) {
    cout << kv.first << ": " << kv.second.count() << " seconds" << endl;
  }

  return 0;
}
