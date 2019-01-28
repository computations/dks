#include <partition.h>
#include <catch2/catch.hpp>
#include "data.h"

TEST_CASE("Minimal Constructor", "[partition]"){
    dks::msa_t msa(data[0]);
}
