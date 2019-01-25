#pragma once
#include "tree.h"
#include <pll.h>
#include <memory>

namespace dks{
    class model_t{
        public:
            model_t(const msa_t& msa): _tree(msa, 0){};
            model_t(const msa_t& msa, uint64_t seed): _tree(msa, seed){};
            unsigned int submodel() const;
            unsigned int rate_categories() const;
        private:
            tree_t _tree;
            std::vector<double> _subst_params;
    };
}
