#include "test_case.h"
#include "partition.h"
#include <random>
#include <exception>

namespace dks{
    benchmark_result_t test_case_t::benchmark(
            const msa_t& msa,
            const model_t& model){
        partition_t partition(msa, model, attributes());
        auto operations = model.make_operations();
        partition.update_partials(operations);
    }

    unsigned int test_case_t::attributes() const{
        return cpu_attributes() | misc_attributes();
    }

    unsigned int test_case_t::misc_attributes() const{
        return _pattern_tip ? PLL_ATTRIB_PATTERN_TIP : 0
             | _site_repeats ? PLL_ATTRIB_SITE_REPEATS : 0
             | _rate_scalers ? PLL_ATTRIB_RATE_SCALERS : 0;
    }

    unsigned int test_case_t::cpu_attributes() const{
        if (test_cpu_t::none == _cpu){
            return PLL_ATTRIB_ARCH_CPU;
        }
        if (test_cpu_t::sse == _cpu){
            return PLL_ATTRIB_ARCH_SSE;
        }
        if (test_cpu_t::avx == _cpu){
            return PLL_ATTRIB_ARCH_AVX;
        }
        if (test_cpu_t::avx2 == _cpu){
            return PLL_ATTRIB_ARCH_AVX2;
        }
        if (test_cpu_t::avx512 == _cpu){
            return PLL_ATTRIB_ARCH_AVX512;
        }
        throw std::runtime_error("Unrecognized CPU type");
    }

}
