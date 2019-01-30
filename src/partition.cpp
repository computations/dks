#include "partition.h"
#include <pll.h>

namespace dks{
    constexpr unsigned int partition_t::_params_indices[];
    constexpr double partition_t::_rate_cats[];
    partition_t::partition_t(const msa_t& msa, const model_t& model, unsigned int attributes){
        unsigned int tip_count = msa.count();
        unsigned int inner_count = tip_count - 2;
        _partition = pll_partition_create(
                    tip_count,                  //tips
                    inner_count,                //clv_buffers
                    msa.states(),               //states
                    msa.length(),               //sites
                    model.submodels(),          //rate_matrices
                    2 * tip_count - 3,          //prob_matrices
                    model.rate_categories(),    //rate_cats
                    inner_count,                //scale_buffes
                    attributes                  //attributes
                    );
        initialize_tips(msa);
        initialize_rates(model);
        update_probability_matrices(model.tree());
    }

    void partition_t::initialize_tips(const msa_t& msa){
        for (size_t tip_id = 0; tip_id < msa.count(); tip_id++) {
            pll_set_tip_states(_partition, 
                                tip_id,
                                msa.char_map(),
                                msa.sequence(tip_id));
        }
    }

    void partition_t::initialize_rates(const model_t& model){
        for (size_t i = 0; i < model.submodels(); i++) {
            pll_set_subst_params(_partition, i, model.subst_params_raw());
            pll_set_frequencies(_partition, i, model.frequencies_raw());
        }
        pll_set_category_rates(_partition, _rate_cats);
    }

    void partition_t::update_probability_matrices(const tree_t& tree){
        pll_update_prob_matrices(_partition,
                                 _params_indices,
                                 tree.matrix_indices().data(),
                                 tree.branch_lengths().data(),
                                 tree.branch_lengths().size());
    }

    void partition_t::update_partials(const std::vector<pll_operation_t>& ops){
        pll_update_partials(_partition, ops.data(), ops.size());
    }

    void partition_t::update_partials(const model_t& model){
        update_partials(model.make_operations());
    }

    double partition_t::loglh(const model_t& model){
        //update_partials(model.make_operations());
        pll_unode_t* parent = model.tree().vroot();
        pll_unode_t* child = parent->back;
        return pll_compute_edge_loglikelihood(_partition,
                                              parent->clv_index,
                                              parent->scaler_index,
                                              child->clv_index,
                                              child->scaler_index,
                                              parent->pmatrix_index,
                                              _params_indices,
                                              nullptr);
    }

    std::vector<double> partition_t::loglh_persite(const model_t& model, size_t sites){
        pll_unode_t* parent = model.tree().vroot();
        pll_unode_t* child = parent->back;

        std::vector<double> persites(sites, 0.0);

        pll_compute_edge_loglikelihood(_partition,
                                       parent->clv_index,
                                       parent->scaler_index,
                                       child->clv_index,
                                       child->scaler_index,
                                       parent->pmatrix_index,
                                       _params_indices,
                                       persites.data());
        return persites;
    }

    partition_t::~partition_t(){
        pll_partition_destroy(_partition);
    }
}
