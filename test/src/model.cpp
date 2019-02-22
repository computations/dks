#include "data.h"
#include <catch2/catch.hpp>
#include <model.h>
#include <partition.h>

TEST_CASE("minimal Constructor for model_t", "[msa][model]") {
  dks::msa_t msa(data[0]);
  dks::model_t model(msa);
  CHECK(model.submodels() == 1);
  CHECK(model.rate_categories() == 1);
  CHECK(model.states() == 4);
  SECTION("substitution parameters") {
    CHECK(model.subst_params().size() == 6);
    for (auto &&r : model.subst_params()) {
      CHECK(r == Approx(1.0));
    }
  }
  SECTION("frequencies") {
    CHECK(model.frequencies().size() == 4);
    for (auto &&r : model.frequencies()) {
      CHECK(r == Approx(0.25));
    }
  }
}

TEST_CASE("constructor with seed for model_t", "[msa][model]") {
  dks::msa_t msa(data[0]);
  dks::model_t model(msa, 123123);
}

TEST_CASE("constructor with pll_partition_t", "[model][pll]") {
  dks::msa_t msa(data[0]);
  dks::model_t model(msa);
  dks::partition_t part(msa, model, 0);
  dks::model_t model_from_part(part.partition_raw());

  REQUIRE(model_from_part.states() == model.states());
  for (size_t i = 0; i < model.subst_params().size(); i++) {
    CHECK(model_from_part.subst_params()[i] == model.subst_params()[i]);
  }

  for (size_t i = 0; i < model.states(); i++) {
    CHECK(model_from_part.frequencies()[i] == model.frequencies()[i]);
  }
}
