#include "data.h"
#include <catch2/catch.hpp>
#include <msa.h>

TEST_CASE("default constructor", "[msa][constructor][default]") {
  dks::msa_t msa;
  CHECK(msa.count() == 0);
  CHECK(msa.length() == 0);
  CHECK(msa.column_entropy() == Approx(0.0));
}

TEST_CASE("fasta file constructor", "[msa][constructor][fasta]") {
  dks::msa_t msa(data[0]);

  CHECK(msa.count() == 767);
  CHECK(msa.length() == 5814);
  CHECK(msa.column_entropy() == Approx(0.2558547326));
}

TEST_CASE("phylip file constructor", "[msa][constructor][phylip]") {
  dks::msa_t msa(data[1]);

  CHECK(msa.count() == 101);
  CHECK(msa.length() == 1858);
  CHECK(msa.column_entropy() == Approx(0.30155679));
}

TEST_CASE("pll_msa_t constructor", "[msa][pll]") {
  pll_phylip_t *fd = pll_phylip_open(data[1], pll_map_phylip);
  pll_msa_t *pll_msa = pll_phylip_parse_interleaved(fd);

  dks::msa_t msa(pll_msa);

  CHECK(msa.count() == 101);
  CHECK(msa.length() == 1858);

  pll_msa_destroy(pll_msa);
  pll_phylip_close(fd);
}

TEST_CASE("protein data", "[msa][protein][phylip]") {
  dks::msa_t msa(data[2]);
  msa.set_states(20);
  CHECK(msa.count() == 775);
  CHECK(msa.length() == 4519);
  CHECK(msa.column_entropy() == Approx(0.190867206));
  CHECK(msa.states() == 20);
  for (size_t i = 0; i < 256; ++i) {
    CHECK(msa.char_map()[i] == pll_map_aa[i]);
  }
}

TEST_CASE("compressed msa") {
  {
    dks::msa_t msa(data[1]);
    dks::msa_compressed_t cmsa(msa);

    CHECK(cmsa.count() == 101);
    CHECK(cmsa.length() == 1630);
    CHECK(cmsa.column_entropy() == Approx(0.3414964886));
  }
  {
    dks::msa_t msa(data[2], 20);
    dks::msa_compressed_t cmsa(msa);

    CHECK(cmsa.count() == 775);
    CHECK(cmsa.length() == 3838);
    CHECK(cmsa.column_entropy() == Approx(0.21699028));
  }
}
