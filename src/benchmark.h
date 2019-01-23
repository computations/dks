#pragma once
#include "test_case.h"
#include <chrono>
#include <memory>

namespace dks{
    enum test_kernel_t{
        partial,
        full,
        derivative,
        pmatrix,
    };
}

template<dks::test_kernel_t TEST_KERNEL, bool SITE_REPEATS>
double benchmark(test_case_t test_case) {
    auto partition = test_case.partition();

    if (TEST_KERNEL == dks::test_kernel_t::full) {
    }
    if (TEST_KERNEL == dks::test_kernel_t::partial) {
    }
    if (TEST_KERNEL == dks::test_kernel_t::derivative) {
    }
    if (TEST_KERNEL == dks::test_kernel_t::pmatrix) {
    }
    return -1.0;
}
