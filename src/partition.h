#pragma once
#include "msa.h"
#include "model.h"
#include <pll.h>
#include <memory>

namespace dks{
    class partition_t{
        public:
            partition_t(
                    unsigned int tips,
                    unsigned int clv_buffers,
                    unsigned int states,
                    unsigned int sites,
                    unsigned int rate_matrices,
                    unsigned int prob_matrices,
                    unsigned int rate_cats,
                    unsigned int scale_buffers,
                    unsigned int attributes
                    ): _partition(pll_partition_create(
                            tips,
                            clv_buffers,
                            states,
                            sites,
                            rate_matrices,
                            prob_matrices,
                            rate_cats,
                            scale_buffers,
                            attributes
                            )){}
            partition_t(const msa_t&, const model_t&, unsigned int);
            ~partition_t();

            void initialize_tips(const msa_t&);
        private:
            std::unique_ptr<pll_partition_t> _partition;
    };
}