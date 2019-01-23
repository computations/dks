#pragma once
#include "msa.h"
#include <memory>
#include <pll.h>

typedef uint32_t test_flags_t;

namespace dks{
    enum test_cpu_t{
        none,
        sse,
        avx,
        avx2,
        avx512,
    };
}

class test_case_t{
public:
    unsigned int tips();
    unsigned int inner_count();
    unsigned int states();
    unsigned int sites();
    unsigned int submodel_count();
    unsigned int gamma_count();
    unsigned int scale_buffers();
    unsigned int attributes();

    std::unique_ptr<pll_partition_t> partition();
    std::unique_ptr<pll_utree_t> tree();
private:
    msa_t _msa;
    size_t _state_count;
    size_t _submodel_count;
    size_t _gamma_class_count;
    dks::test_cpu_t _cpu;
    uint64_t _random_seed;
};
