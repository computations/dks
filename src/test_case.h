#pragma once
#include "msa.h"
#include "tree.h"
#include "model.h"
#include <pll.h>
#include <memory>
#include <unordered_map>

namespace dks{
    enum test_cpu_t{
        none,
        sse,
        avx,
        avx2,
        avx512,
    };

    enum test_kernel_t{
        partial,
        likelihood,
        derivative,
        pmatrix,
    };

    typedef std::unordered_map<test_kernel_t, double> benchmark_result_t;

    class test_case_t{
        public:
            benchmark_result_t benchmark(msa_t, model_t);
        private:
            test_cpu_t _cpu;
            uint64_t _random_seed;
            bool _site_repeats;
            bool _tip_inner_optimization;
            bool _rate_scalers;
    };
}
