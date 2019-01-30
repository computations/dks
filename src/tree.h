#pragma once
#include "msa.h"
#include <memory>
#include <utility>

namespace dks{
    class tree_t {
        public:
            tree_t(const msa_t& msa, uint64_t seed);
            tree_t(const msa_t& msa): tree_t(msa, 0) {}
            pll_unode_t* vroot() const;
            size_t node_count() const;
            size_t edge_count() const;
            const std::vector<double>& branch_lengths() const;
            const std::vector<unsigned int>& matrix_indices() const;
            std::vector<pll_unode_t*> full_traverse() const;
            ~tree_t();
        private:
            static void insert_tip(pll_unode_t*, const char*);
            static void pair_nodes(pll_unode_t*, pll_unode_t*);
            static void make_circle(pll_unode_t*, pll_unode_t*, pll_unode_t*);
            static pll_unode_t* make_triplet(pll_unode_t*, pll_unode_t*, pll_unode_t*);
            static pll_unode_t* make_node();
            static pll_unode_t* make_tip(const char*);

            void fill_branch_lengths(const std::vector<pll_unode_t*>&);
            void fill_matrix_indices(const std::vector<pll_unode_t*>&);

            void update_internal_lists();

            pll_utree_t* _tree;
            std::vector<double> _branch_lengths;
            std::vector<unsigned int> _matrix_indices;
    };
}
