#include <tree.h>
#include <catch2/catch.hpp>

TEST_CASE("tree minimal constructor and operations", "[tree]"){
    dks::msa_t msa("data/101.phy");
    dks::tree_t tree(msa);
    CHECK(tree.node_count() == (101 * 2 - 2));
    SECTION("Branch lengths"){
        REQUIRE(tree.branch_lengths().size() > 0);
        for (auto && brlen : tree.branch_lengths()){
            CHECK(brlen >= Approx(0.0));
        }
    }
    SECTION("Matrix indices"){
        REQUIRE(tree.matrix_indices().size() > 0);
    }
}
