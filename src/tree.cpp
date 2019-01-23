#include "tree.h"
#include "pll.h"
#include <random>

namespace dks{
    tree_t::tree_t(msa_t msa, uint64_t random_seed) {
        _tree.tip_count = msa.count();
        _tree.edge_count = 2*_tree.tip_count - 3;
        _tree.inner_count = _tree.tip_count - 2;

        _tree.vroot = make_triplet(
                make_tip(msa.label(0)),
                make_tip(msa.label(1)),
                make_tip(msa.label(2))
            );
        //generate a list of nodes
        size_t node_buffer_size = _tree.tip_count + 3 * _tree.inner_count;
        pll_unode_t** nodes = (pll_unode_t**)malloc(sizeof(pll_unode_t*) *
                node_buffer_size);

        std::minstd_rand random_engine(random_seed);

        for (size_t i = 3; i < _tree.tip_count ; i++) {
            unsigned int node_count;
            pll_utree_traverse(
                    _tree.vroot,
                    PLL_TREE_TRAVERSE_POSTORDER,
                    nullptr,
                    nodes,
                    &node_count);

            std::uniform_int_distribution<> roller(0, node_count-1);
            pll_unode_t* insert_node = nodes[roller(random_engine)];
            insert_tip(insert_node, msa.label(i));
        }
    }

    tree_t::~tree_t(){
        free(_tree.nodes);
    }

    void tree_t::insert_tip(pll_unode_t* insert_node, char* label){
        pll_unode_t* new_a = (pll_unode_t*)malloc(sizeof(pll_unode_t));
        pll_unode_t* new_b = (pll_unode_t*)malloc(sizeof(pll_unode_t));
        pll_unode_t* new_c = (pll_unode_t*)malloc(sizeof(pll_unode_t));
        pll_unode_t* new_tip = make_tip(label);

        pll_unode_t* saved_back = insert_node->back;

        pair_nodes(insert_node, new_a);
        pair_nodes(saved_back, new_b);
        pair_nodes(new_tip, new_c);

        make_circle(new_a, new_b, new_c);

        new_tip->label = label;
        new_tip->next = nullptr;
    }

    void tree_t::pair_nodes(pll_unode_t* a, pll_unode_t* b){
        a->back = b;
        b->back = a;
    }

    void tree_t::make_circle(pll_unode_t* a, pll_unode_t* b, pll_unode_t* c){
        a->next = b;
        b->next = c;
        c->next = a;
    }

    pll_unode_t* tree_t::make_triplet(pll_unode_t* a, pll_unode_t* b, pll_unode_t* c){
        pll_unode_t* inner_a = (pll_unode_t*)malloc(sizeof(pll_unode_t));
        pll_unode_t* inner_b = (pll_unode_t*)malloc(sizeof(pll_unode_t));
        pll_unode_t* inner_c = (pll_unode_t*)malloc(sizeof(pll_unode_t));

        pair_nodes(inner_a, a);
        pair_nodes(inner_b, b);
        pair_nodes(inner_c, c);

        make_circle(inner_a, inner_b, inner_c);
        return inner_a;
    }

    pll_unode_t* tree_t::make_tip(char* label){
        pll_unode_t* a = (pll_unode_t*)malloc(sizeof(pll_unode_t));
        a->label = label;
        a->next = nullptr;
        a->back = nullptr;
        return a;
    }
}
