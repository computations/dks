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
        benchmark_time_t>
            benchmark_result_t;

    struct attributes_t {
        bool pattern_tip;
        bool tip_inner;
        bool site_repeats;
        bool rate_scalers;
        test_cpu_t simd;

        attributes_t() = default;

        attributes_t(bool pc, bool ti, bool sr, bool rs, test_cpu_t simd):
            pattern_tip {pc},
            tip_inner {ti},
            site_repeats {sr},
            rate_scalers {rs},
            simd {simd} {};

        bool operator==(const attributes_t& other) const {
            return pattern_tip == other.pattern_tip
                && tip_inner == other.tip_inner
                && site_repeats == other.site_repeats
                && rate_scalers == other.rate_scalers
                && simd == other.simd;
        }
    };

    class test_case_t{
        public:
            test_case_t() :
                _cpu {test_cpu_t::none},
                _trials {10},
                _random_seed {0},
                _pattern_tip {false},
                _site_repeats {false},
                _rate_scalers {false} {}

            test_case_t(
                    test_cpu_t cpu,
                    bool pt,
                    bool sr,
                    bool rs,
                    uint64_t seed):
                _cpu{cpu},
                _trials{20},
                _random_seed{seed},
                _pattern_tip{pt},
                _site_repeats{sr},
                _rate_scalers{rs} {}

            test_case_t(test_cpu_t cpu):
                test_case_t {cpu, 0, 0, 0, 0} {}

            test_case_t(const attributes_t& attribs):
                test_case_t (attribs.simd,
                             attribs.pattern_tip,
                             attribs.site_repeats,
                             attribs.rate_scalers,
                             0) {};

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

namespace std {
    template<> struct hash<dks::attributes_t> {
        typedef dks::attributes_t argument_type;
        typedef size_t result_type;
        result_type operator() (const argument_type& s) const noexcept {
            return (s.pattern_tip << 0)
                 ^ (s.tip_inner << 1)
                 ^ (s.site_repeats << 2)
                 ^ (s.rate_scalers << 3)
                 ^ (s.simd << 4);
        }
    };
}
