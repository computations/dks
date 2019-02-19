#include "benchmark.h"
#include "partition.h"
#include "msa.h"
#include <utility>

namespace dks{

    model_t extract_model(const pll_partition_t* pll_partition) {
        return std::move(model_t(
                    pll_partition->tips,
                    pll_partition->states,
                    pll_partition->subst_params,
                    pll_partition->frequencies));
    }

    attributes_t select_kernel(
            const pll_partition_t* pll_partition,
            const pll_msa_t* msa,
            kernel_weight_t kw) {
    }
}
