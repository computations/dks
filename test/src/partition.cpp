#include <partition.h>
#include <test_case.h>
#include <catch2/catch.hpp>
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

    dks::partition_t partition(msa, model, test_case.attributes());
    SECTION("update partials, operations specified"){
        partition.update_partials(model.make_operations());
    }

    SECTION("update partials, with model"){
        partition.update_partials(model);
    }
}
