#pragma once
#include "tree.h"
#include <pll.h>
#include <memory>
#include <vector>

namespace dks{
    class model_t{
        public:
            model_t(const msa_t& msa): _tree(msa, 0), _subst_params(6, 0.0){};
            model_t(const msa_t& msa, uint64_t seed): _tree(msa, seed){};
            unsigned int submodels() const;
            unsigned int rate_categories() const;
            const double * subst_params() const;

            std::vector<pll_operation_t> make_operations() const;
        private:
            tree_t _tree;
            std::vector<double> _subst_params;
            std::vector<double> _frequencies;
    };
}
