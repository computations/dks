#pragma once
#include "msa.h"
#include "tree.h"
#include "model.h"
#include "partition.h"
#include <pll.h>
#include <chrono>
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

    typedef std::chrono::duration<double> benchmark_time_t;

    typedef std::unordered_map<
        test_kernel_t,
        benchmark_time_t
            > benchmark_result_t;

    class test_case_t{
        public:
            test_case_t() : 
                _cpu(test_cpu_t::none),
                _trials(30),
                _random_seed(0),
                _pattern_tip(0),
                _site_repeats(0),
                _rate_scalers(0) {}

            test_case_t(
                    test_cpu_t cpu,
                    bool pt,
                    bool sr,
                    bool rs,
                    uint64_t seed):
                _cpu(cpu),
                _trials(30),
                _random_seed(seed),
                _pattern_tip(pt),
                _site_repeats(sr),
                _rate_scalers(rs) {}

            test_case_t(
                    test_cpu_t cpu):
                test_case_t(cpu, 0, 0, 0, 0){}

            benchmark_result_t benchmark(const msa_t&, const model_t&);
            benchmark_time_t benchmark_partials(
                    partition_t& partition,
                    const model_t& model);
            benchmark_time_t benchmark_likelihood(
                    partition_t& partition,
                    const model_t& model);
            benchmark_time_t benchmark_pmatrix(
                    partition_t& partition,
                    const model_t& model);
            benchmark_time_t benchmark_derivative(
                    partition_t& partition,
                    const model_t& model);
            unsigned int attributes() const;
            unsigned int cpu_attributes() const;
            unsigned int misc_attributes() const;
        private:
            test_cpu_t _cpu;
            size_t _trials;
            uint64_t _random_seed;
            bool _pattern_tip;
            bool _site_repeats;
            bool _rate_scalers;
    };
}
