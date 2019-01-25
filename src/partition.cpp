#include "partition.h"
#include <pll.h>

namespace dks{
    partition_t::partition_t(const msa_t& msa, const model_t& model, unsigned int attributes){
        unsigned int tip_count = msa.count();
        unsigned int inner_count = tip_count - 2;
        _partition.reset(pll_partition_create(
                    tip_count, //tips
                    inner_count, //clv_buffers
                    msa.states(), //states
                    msa.length(), //sites
                    model.submodel(), //rate_matrices
                    2 * tip_count - 3, //prob_matrices
                    model.rate_categories(),//rate_cats
                    inner_count,
                    attributes));
    }

    void partition_t::initialize_tips(const msa_t& msa){
        for (size_t tip_id = 0; tip_id < msa.count(); tip_id++) {
            pll_set_tip_states(_partition.get(), 
                                tip_id,
                                msa.char_map(),
                                msa.sequence(tip_id));
        }
    }

    partition_t::~partition_t(){
        pll_partition_destroy(_partition.get());
    }
}