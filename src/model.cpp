#include "model.h"
#include <pll.h>

namespace dks{
    unsigned int model_t::submodels() const{
        return 1;
    }

    unsigned int model_t::rate_categories() const{
        return 1;
    }

    const double * model_t::subst_params_raw() const{
        return _subst_params.data();
    }

    const std::vector<double>& model_t::subst_params() const{
        return _subst_params;
    }

    const double * model_t::frequencies_raw() const{
        return _frequencies.data();
    }

    const std::vector<double>& model_t::frequencies() const{
        return _frequencies;
    }

    std::vector<pll_operation_t> model_t::make_operations() const{
        pll_unode_t** traversal_nodes = (pll_unode_t**)malloc(
                sizeof(pll_unode_t*) * _tree.node_count());
        unsigned int traversal_size=0;
        pll_utree_traverse(_tree.vroot(),
                           PLL_TREE_TRAVERSE_POSTORDER,
                           nullptr,
                           traversal_nodes,
                           &traversal_size);
        std::vector<pll_operation_t> operations(traversal_size);
        unsigned int operations_count = 0;
        pll_utree_create_operations(traversal_nodes,
                                    traversal_size,
                                    nullptr,
                                    nullptr,
                                    operations.data(),
                                    nullptr,
                                    &operations_count);

        return operations;
    }
}
