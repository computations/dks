#pragma once
#include "tree.h"
#include <pll.h>
#include <memory>
#include <vector>

namespace dks{
    class model_t{
        public:
            model_t(const msa_t& msa): model_t(msa, 0){};
            model_t(const msa_t& msa, uint64_t seed): 
                _tree(msa, seed),
                _subst_params(6, 0.0),
                _frequencies(4, .25)
            {};
            unsigned int submodels() const;
            unsigned int rate_categories() const;
            const double * subst_params_raw() const;
            const std::vector<double>& subst_params() const;
            const double * frequencies_raw() const;
            const std::vector<double>& frequencies() const;

            std::vector<pll_operation_t> make_operations() const;
        private:
            tree_t _tree;
            std::vector<double> _subst_params;
            std::vector<double> _frequencies;
    };
}
