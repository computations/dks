#include <catch2/catch.hpp>
#include <test_case.h>
#include "data.h"

TEST_CASE("test_case_t basic operations", "[test_case][constructor]"){
    dks::test_case_t t;
    SECTION("Attributes"){
        unsigned int cpu_attrs = t.cpu_attributes();
        CHECK((cpu_attrs & PLL_ATTRIB_ARCH_SSE) == 0);
        CHECK((cpu_attrs & PLL_ATTRIB_ARCH_AVX) == 0);
        CHECK((cpu_attrs & PLL_ATTRIB_ARCH_AVX2)== 0);
        CHECK((cpu_attrs & PLL_ATTRIB_ARCH_AVX512) == 0);

        unsigned int attrs = t.attributes();
        CHECK((attrs & PLL_ATTRIB_ARCH_MASK) == cpu_attrs);
    }
}

TEST_CASE("Benchmarks", "[test_case][benchmarks"){
    dks::test_case_t t;
    dks::msa_t msa(data[1]);
    dks::model_t model(msa);
    auto br = t.benchmark(msa, model);
    CHECK(br[dks::test_kernel_t::partial].count() >= 0.0);
}

TEST_CASE("Result type check",  "[test_case][benchmark_result]"){
    dks::benchmark_result_t res;
    res[dks::test_kernel_t::partial] = std::chrono::duration<double>(1.0);
    CHECK(res[dks::test_kernel_t::partial] == std::chrono::duration<double>(1.0));
}
