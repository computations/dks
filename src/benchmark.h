#pragma once
#include "test_case.h"
#include <unordered_map>

namespace dks {
typedef std::unordered_map<test_kernel_t, double> kernel_weight_t;

attributes_t select_kernel(const pll_partition_t *, const pll_msa_t *,
                           const kernel_weight_t &);

attributes_t select_kernel(const model_t &, const msa_t &,
                           const kernel_weight_t &);
} // namespace dks
