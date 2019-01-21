#include "test_case.h"

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
