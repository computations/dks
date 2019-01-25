#include "msa.h"

namespace dks{
    msa_t::msa_t(const pll_msa_t* msa){
        for (int i = 0; i < msa->count; i++) {
            _labels.emplace_back(msa->label[i]);
            _sequences.emplace_back(msa->sequence[i], msa->sequence[i]+msa->length);
        }
        _states = 4;
    }

    size_t msa_t::count() const{
        return _labels.size();
    }

    size_t msa_t::length() const{
        if (_sequences.empty()){return 0;}
        return _sequences.front().size();
    }

    size_t msa_t::states() const{
        return _states;
    }

    char* msa_t::label(size_t i){
        return _labels[i];
    }

    const char* msa_t::sequence(size_t i) const{
        return _sequences[i].data();
    }

    const pll_state_t* msa_t::char_map() const{
        return pll_map_nt;
    }
}
