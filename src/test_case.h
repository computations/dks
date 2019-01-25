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
            test_case_t() = default;
            test_case_t(
                    test_cpu_t cpu,
                    bool pt,
                    bool sr,
                    bool rs,
                    uint64_t seed):
                _cpu(cpu),
                _random_seed(seed),
                _pattern_tip(pt),
                _site_repeats(sr),
                _rate_scalers(rs) {}

            benchmark_result_t benchmark(const msa_t&, const model_t&);
            unsigned int attributes() const;
            unsigned int cpu_attributes() const;
            unsigned int misc_attributes() const;
        private:
            test_cpu_t _cpu;
            uint64_t _random_seed;
            bool _pattern_tip;
            bool _site_repeats;
            bool _rate_scalers;
    };
}
