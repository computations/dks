#include <tree.h>
#include <catch2/catch.hpp>

TEST_CASE("tree minimal constructor", "[tree]"){
    dks::msa_t msa("data/101.phy");
    dks::tree_t tree(msa);
}
