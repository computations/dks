#include <model.h>
#include <catch2/catch.hpp>
#include "data.h"

TEST_CASE("Minimal Constructor for model_t", "[msa][model]") {
    dks::msa_t msa(data[0]);
    dks::model_t model(msa);
    CHECK(model.submodels() == 1);
    CHECK(model.rate_categories() == 1);
    SECTION("substitution parameters") {
        CHECK(model.subst_params().size() == 6);
        for(auto&& r : model.subst_params()) {
            CHECK(r >= Approx(0.0));
        }
    }
    SECTION("frequencies") {
        CHECK(model.frequencies().size() == 4);
        for(auto&& r : model.frequencies()) {
            CHECK(r >= Approx(0.0));
        }
    }
}

TEST_CASE("Constructor with seed for model_t", "[msa][model]") {
    dks::msa_t msa(data[0]);
    dks::model_t model(msa, 123123);
}
