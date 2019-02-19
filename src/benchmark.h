#pragma once
#include "test_case.h"
#include <unordered_map>

namespace dks{

    struct attributes_t {
        bool pattern_compression;
        bool tip_inner;
        bool site_repeats;
        bool rate_scalers;
        test_cpu_t simd;
    };

    typedef std::unordered_map<test_kernel_t, double> kernel_weight_t;

    attributes_t select_kernel(const pll_partition_t*, kernel_weight_t);
}
