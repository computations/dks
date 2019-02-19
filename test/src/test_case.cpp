#include <catch2/catch.hpp>
#include <test_case.h>
#include "data.h"

TEST_CASE("test_case_t basic operations", "[test_case][constructor]") {
    dks::test_case_t t;
    SECTION("Attributes") {
        unsigned int cpu_attrs = t.cpu_attributes();
        CHECK((cpu_attrs & PLL_ATTRIB_ARCH_SSE) == 0);
        CHECK((cpu_attrs & PLL_ATTRIB_ARCH_AVX) == 0);
        CHECK((cpu_attrs & PLL_ATTRIB_ARCH_AVX2)== 0);
        CHECK((cpu_attrs & PLL_ATTRIB_ARCH_AVX512) == 0);

        unsigned int attrs = t.attributes();
        CHECK((attrs & PLL_ATTRIB_ARCH_MASK) == cpu_attrs);
    }
}

TEST_CASE("benchmarks", "[test_case][benchmarks") {
    dks::test_case_t t;
    dks::msa_t msa(data[1]);
    dks::model_t model(msa);
    auto br = t.benchmark(msa, model);
    CHECK(br[dks::test_kernel_t::partial].count() >= 0.0);
    CHECK(br[dks::test_kernel_t::likelihood].count() >= 0.0);
    CHECK(br[dks::test_kernel_t::pmatrix].count() >= 0.0);
    CHECK(br[dks::test_kernel_t::derivative].count() >= 0.0);
}

TEST_CASE("result type check",  "[test_case][benchmark_result]") {
    dks::benchmark_result_t res;
    res[dks::test_kernel_t::partial] = std::chrono::duration<double>(1.0);
    CHECK(res[dks::test_kernel_t::partial] == std::chrono::duration<double>(1.0));
}

void test_attributes(
        const dks::test_case_t& test_case,
        bool pt,
        bool sr,
        bool rs) {
    CHECK((((test_case.attributes() & PLL_ATTRIB_PATTERN_TIP) && pt) ||
          (!(test_case.attributes() & PLL_ATTRIB_PATTERN_TIP && !pt))));
    CHECK((((test_case.attributes() & PLL_ATTRIB_RATE_SCALERS) && rs) ||
          (!(test_case.attributes() & PLL_ATTRIB_RATE_SCALERS && !rs))));
    CHECK((((test_case.attributes() & PLL_ATTRIB_SITE_REPEATS) && sr) ||
          (!(test_case.attributes() & PLL_ATTRIB_SITE_REPEATS && !sr))));
}

TEST_CASE("various constructors for test_case_t", "[test_case][attributes]") {
    std::vector<std::pair<std::string, dks::test_cpu_t>> cpus = {
        std::make_pair("cpu none", dks::test_cpu_t::none),
        std::make_pair("cpu sse", dks::test_cpu_t::sse),
        std::make_pair("cpu avx", dks::test_cpu_t::avx),
        std::make_pair("cpu avx2", dks::test_cpu_t::avx2),
    };

    std::vector<std::pair<std::string, bool>> pattern_tips = {
        std::make_pair("pattern tips off", false),
        std::make_pair("pattern tips on", true),
    };

    std::vector<std::pair<std::string, bool>> site_repeats = {
        std::make_pair("site repeats off", false),
        std::make_pair("site repeats on", true),
    };

    std::vector<std::pair<std::string, bool>> rate_scalers = {
        std::make_pair("rate scalers off", false),
        std::make_pair("rate scalers on", true),
    };

    for (auto&& cpu : cpus){
        for (auto&& pt : pattern_tips){
            for (auto&& sr : site_repeats){
                for (auto&& rs : rate_scalers){
                    SECTION(cpu.first + ", " +
                            pt.first + ", " +
                            sr.first + ", " +
                            rs.first) {
                        dks::test_case_t test_case(cpu.second,
                                pt.second,
                                sr.second,
                                rs.second, 0);
                        test_attributes(
                                test_case,
                                pt.second,
                                sr.second,
                                rs.second);
                    }
                }
            }
        }
    }
}
