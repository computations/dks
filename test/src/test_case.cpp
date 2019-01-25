#include <catch2/catch.hpp>
#include <test_case.h>

TEST_CASE("Default constructor" "[test_case][constructor]"){
    dks::test_case_t t;
}

TEST_CASE("Result type check",  "[test_case][benchmark_result]"){
    dks::benchmark_result_t res;
    res[dks::test_kernel_t::partial] = 1.0;
    CHECK(res[dks::test_kernel_t::partial] == 1.0);
}
