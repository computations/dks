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
    CHECK(msa.states() == 4);
}

TEST_CASE("phylip file constructor", "[msa][constructor][phylip]") {
    dks::msa_t msa(data[1]);

    CHECK(msa.count() == 101);
    CHECK(msa.length() == 1858);
    CHECK(msa.states() == 4);
}

TEST_CASE("pll_msa_t constructor", "[msa][pll]") {
    pll_phylip_t* fd = pll_phylip_open(data[1], pll_map_phylip);
    pll_msa_t* pll_msa = pll_phylip_parse_interleaved(fd);

    dks::msa_t msa(pll_msa);

    CHECK(msa.count() == 101);
    CHECK(msa.length() == 1858);
    CHECK(msa.states() == 4);

    pll_msa_destroy(pll_msa);
    pll_phylip_close(fd);
}

TEST_CASE("compressed msa") {
    dks::msa_t msa(data[1]);
    dks::msa_compressed_t cmsa(msa);

    CHECK(cmsa.count() == 101);
    CHECK(msa.length() == 1858);
    CHECK(msa.states() == 4);
}
