#include <partition.h>
#include <test_case.h>
#include <catch2/catch.hpp>
#include <cmath>
#include <utility>
#include "data.h"

void test_partition_operations(
        const dks::test_case_t& test_case,
        const dks::model_t& model,
        const dks::msa_t& msa) {

    SECTION("check attributes") {
        dks::partition_t partition(msa, model, test_case.attributes());
        REQUIRE(partition.attributes() == test_case.attributes());
    }

    SECTION("update partials, operations specified") {
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model.make_operations());
    }

    SECTION("update partials, with model") {
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model);
    }

    SECTION("per site loglh") {
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model);
        auto loglh_persite = partition.loglh_persite(model, msa.length());
        for(auto&& loglh : loglh_persite) {
            CHECK(loglh <= Approx(0.0));
            CHECK(std::isfinite(loglh));
        }
    }

    SECTION("loglh") {
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model);
        double loglh = partition.loglh(model);
        CHECK(loglh <= Approx(0.0));
        CHECK(std::isfinite(loglh));
    }

    SECTION("update sumtable") {
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_sumtable(model.tree());
    }

    SECTION("Derivatives") {
        dks::partition_t partition(msa, model, test_case.attributes());
        partition.update_partials(model);
        partition.update_sumtable(model.tree());
        auto dl = partition.compute_derivative(model.tree());
        CHECK(std::isfinite(dl.first));
        CHECK(std::isfinite(dl.second));
    }
}


TEST_CASE("Minimal Constructor for partition_t", "[partition][msa][model]") {
    dks::msa_t msa(data[1]);
    dks::model_t model(msa);
    dks::test_case_t test_case;
    dks::partition_t partition(msa, model, test_case.attributes());
}

TEST_CASE("basic operations on partition_t", "[partition]") {

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
        //std::make_pair("site repeats on", true),
    };

    std::vector<std::pair<std::string, bool>> rate_scalers = {
        std::make_pair("rate scalers off", false),
        //std::make_pair("rate scalers on", true),
    };

    dks::msa_t msa(data[1]);
    dks::model_t model(msa);

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
                        test_partition_operations(test_case, model, msa);
                    }
                }
            }
        }
    }
}
