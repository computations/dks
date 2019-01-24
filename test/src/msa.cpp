#include <msa.h>
#include <catch2/catch.hpp>

TEST_CASE("default constructor", "[msa][constructor]"){
    dks::msa_t msa;
    CHECK(msa.count() == 0);
    CHECK(msa.width() == 0);
}
