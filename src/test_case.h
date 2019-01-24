#pragma once
#include "msa.h"
#include "tree.h"
#include "model.h"
#include <memory>
#include <pll.h>


namespace dks{
    typedef uint32_t test_flags_t;

    enum test_cpu_t{
        none,
        sse,
        avx,
        avx2,
        avx512,
    };

    enum test_kernel_t{
        partial,
        full,
        derivative,
        pmatrix,
    };

    class test_case_t{
        public:
            double benchmark(msa_t, model_t);
        private:
            test_cpu_t _cpu;
            test_kernel_t _kernel;
            uint64_t _random_seed;
            bool _site_repeats;
            bool _tip_inner_optimization;
            bool _rate_scalers;
    };
}
