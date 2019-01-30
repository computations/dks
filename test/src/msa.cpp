#include <msa.h>
#include <catch2/catch.hpp>
#include "data.h"

TEST_CASE("default constructor", "[msa][constructor][default]") {
    dks::msa_t msa;
    CHECK(msa.count() == 0);
    CHECK(msa.length() == 0);
}

TEST_CASE("fasta file constructor", "[msa][constructor][fasta]") {
    dks::msa_t msa(data[0]);

    CHECK(msa.count() == 767);
    CHECK(msa.length() == 5814);
}

TEST_CASE("phylip file constructor", "[msa][constructor][phylip]") {
    dks::msa_t msa(data[1]);

    CHECK(msa.count() == 101);
    CHECK(msa.length() == 1858);
}
