#include <model.h>
#include <catch2/catch.hpp>
#include "data.h"

TEST_CASE("Minimal Constructor for model_t", "[msa][model]"){
    dks::msa_t msa(data[0]);
    dks::model_t model(msa);
    CHECK(model.submodels() == 1);
    CHECK(model.rate_categories() == 1);
}

TEST_CASE("Constructor with seed for model_t", "[msa][model]"){
    dks::msa_t msa(data[0]);
    dks::model_t model(msa, 123123);
}
