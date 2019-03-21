#include "data.h"
#include <benchmark.h>
#include <catch2/catch.hpp>

TEST_CASE("benchmark simple", "[benchmark]") {
  dks::msa_t msa(data[0]);
  dks::model_t model(msa);

  dks::kernel_weight_t kw{
      {dks::test_kernel_t::partial, 0.25},
      {dks::test_kernel_t::likelihood, 0.25},
      {dks::test_kernel_t::derivative, 0.25},
      {dks::test_kernel_t::pmatrix, 0.25},
  };

  dks::select_kernel(model, msa, kw, false);
}

TEST_CASE("test suggest weights") {
  SECTION("data set 0") {
    dks::msa_t msa(data[0]);
    dks::kernel_weight_t kw = suggest_weights(msa);
    CHECK(kw[dks::test_kernel_t::partial] == Approx(48.3655022808));
    CHECK(kw[dks::test_kernel_t::likelihood] == Approx(28.4610818168));
    CHECK(kw[dks::test_kernel_t::derivative] == Approx(20.0649561802));
    CHECK(kw[dks::test_kernel_t::pmatrix] == Approx(10.7185013778));
  }
  SECTION("data set 1") {
    dks::msa_t msa(data[1]);
    dks::kernel_weight_t kw = suggest_weights(msa);
    CHECK(kw[dks::test_kernel_t::partial] == Approx(43.7066779955));
    CHECK(kw[dks::test_kernel_t::likelihood] == Approx(31.1405383016));
    CHECK(kw[dks::test_kernel_t::derivative] == Approx(22.6850948355));
    CHECK(kw[dks::test_kernel_t::pmatrix] == Approx(5.1910883766));
  }
  SECTION("data set 2") {
    dks::msa_t msa(data[2]);
    dks::kernel_weight_t kw = suggest_weights(msa);
    CHECK(kw[dks::test_kernel_t::partial] == Approx(48.4579732006));
    CHECK(kw[dks::test_kernel_t::likelihood] == Approx(28.2558142408));
    CHECK(kw[dks::test_kernel_t::derivative] == Approx(20.0304750289));
    CHECK(kw[dks::test_kernel_t::pmatrix] == Approx(8.9090979813));
  }
}
