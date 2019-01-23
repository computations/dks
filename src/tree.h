#pragma once
#include "msa.h"
#include <memory>

namespace dks{
    class tree_t {
        public:
            tree_t(msa_t msa, uint64_t seed);
            ~tree_t();
        private:
            static void insert_tip(pll_unode_t*, char*);
            static void pair_nodes(pll_unode_t*, pll_unode_t*);
            static void make_circle(pll_unode_t*, pll_unode_t*, pll_unode_t*);
            static pll_unode_t* make_triplet(pll_unode_t*, pll_unode_t*, pll_unode_t*);
            static pll_unode_t* make_tip(char*);

            pll_utree_t _tree;
    };
}
