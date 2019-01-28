#include <partition.h>
#include <test_case.h>
#include <catch2/catch.hpp>
#include "data.h"

TEST_CASE("Minimal Constructor for partition_t", "[partition][msa][model]"){
    dks::msa_t msa(data[0]);
    dks::model_t model(msa);
    dks::test_case_t test_case;
    dks::partition_t partition(msa, model, test_case.attributes());
}
