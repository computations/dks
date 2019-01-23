#include "test_case.h"
#include <exception>
#include <iostream>
#include <random>

unsigned int test_case_t::tips(){
    return _msa.count();
}

unsigned int test_case_t::inner_count(){
    //TODO: Add logic for rooted trees
    return _msa.count() - 3;
}

unsigned int test_case_t::states(){
    return _state_count;
}

unsigned int test_case_t::sites(){
    return _msa.width();
}

unsigned int test_case_t::submodel_count(){
    return _submodel_count;
}

unsigned int test_case_t::gamma_count(){
    return _gamma_class_count;
}

unsigned int test_case_t::attributes(){
    switch(_cpu){
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
            throw std::invalid_argument("Unrecognized CPU Type");
    }
}

std::unique_ptr<pll_partition_t> test_case_t::partition(){
    return std::unique_ptr<pll_partition_t>(pll_partition_create(
                            tips(),           /* tips             */
                            inner_count(),    /* clv_buffers      */
                            states(),         /* states           */
                            sites(),          /* sites            */
                            submodel_count(), /* rate_matrices    */
                            inner_count(),    /* prob_matrices    */
                            gamma_count(),    /* rate_cats        */
                            inner_count(),    /* scale_buffers    */
                            attributes()      /* attributes       */
                ));
}
