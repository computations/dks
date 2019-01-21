#pragma once
#include "test_case.h"
#include <chrono>
#include <memory>
#include <exception>

#include <pll.h>

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
        full,
        derivative,
        pmatrix,
    };

    unsigned int generate_attributes(test_cpu_t cputype){
        switch(cputype){
            case dks::test_cpu_t::none:
                return PLL_ATTRIB_ARCH_CPU;
            case dks::test_cpu_t::sse:
                return PLL_ATTRIB_ARCH_SSE;
            case dks::test_cpu_t::avx:
                return PLL_ATTRIB_ARCH_AVX;
            case dks::test_cpu_t::avx2:
                return PLL_ATTRIB_ARCH_AVX2;
            case dks::test_cpu_t::avx512:
                return PLL_ATTRIB_ARCH_AVX512;
            default:
                throw std::invalid_argument("CPU type not recognized");
        }
    }
}

template<dks::test_kernel_t TEST_KERNEL, dks::test_cpu_t TEST_CPU, bool SITE_REPEATS>
double benchmark(test_case_t test_case) {
    unsigned int attrs = dks::generate_attributes(TEST_CPU);
    attrs |= test_case.attributes();
    std::unique_ptr<pll_partition_t> partition(pll_partition_create(
                            test_case.tips(),           /* tips             */
                            test_case.inner_count(),    /* clv_buffers      */
                            test_case.states(),         /* states           */
                            test_case.sites(),          /* sites            */
                            test_case.submodel_count(), /* rate_matrices    */
                            test_case.inner_count(),    /* prob_matrices    */
                            test_case.gamma_count(),    /* rate_cats        */
                            test_case.inner_count(),    /* scale_buffers    */
                            attrs                       /* attributes       */
                ));

    if (TEST_KERNEL == dks::test_kernel_t::partial) {
    }
    if (TEST_KERNEL == dks::test_kernel_t::full) {
    }
    if (TEST_KERNEL == dks::test_kernel_t::derivative) {
    }
    if (TEST_KERNEL == dks::test_kernel_t::pmatrix) {
    }
    return -1.0;
}
