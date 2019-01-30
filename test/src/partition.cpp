#include <partition.h>
#include <test_case.h>
#include <catch2/catch.hpp>
#include <cmath>
#include <iostream>
#include "data.h"

TEST_CASE("Minimal Constructor for partition_t", "[partition][msa][model]"){
    dks::msa_t msa(data[1]);
    dks::model_t model(msa);
    dks::test_case_t test_case;
    dks::partition_t partition(msa, model, test_case.attributes());
}

TEST_CASE("basic operations on partition_t", "[partition]"){
    dks::msa_t msa(data[1]);
    dks::model_t model(msa);
    dks::test_case_t test_case;

    SECTION("update partials, operations specified"){
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model.make_operations());
    }

    SECTION("update partials, with model"){
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model);
    }

    SECTION("per site loglh"){
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model);
        auto loglh_persite = partition.loglh_persite(model, msa.length());
        for(auto&& loglh : loglh_persite){
            CHECK(loglh <= Approx(0.0));
            CHECK(std::isfinite(loglh));
        }
    }

    SECTION("loglh"){
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model);
        double loglh = partition.loglh(model);
        CHECK(loglh <= Approx(0.0));
        CHECK(std::isfinite(loglh));
    }
}
