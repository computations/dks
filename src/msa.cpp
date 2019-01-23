#include "msa.h"

msa_t::msa_t(const pll_msa_t* msa){
    for (int i = 0; i < msa->count; i++) {
        _labels.emplace_back(msa->label[i]);
        _sequences.emplace_back(msa->sequence[i], msa->sequence[i]+msa->length);
    }
}

size_t msa_t::count(){
    return _labels.size();
}

size_t msa_t::width(){
    return _sequences[0].size();
}

char* msa_t::label(size_t i){
    return _labels[i];
}
