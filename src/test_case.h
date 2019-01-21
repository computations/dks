#pragma once
#include "msa.h"

typedef uint32_t test_flags_t;

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
private:
    msa_t _msa;
    size_t _state_count;
    size_t _submodel_count;
    size_t _gamma_class_count;
};
