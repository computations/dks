#include "data.h"
#include <benchmark.h>
#include <catch2/catch.hpp>

TEST_CASE("benchmark simple") {
  dks::msa_t msa(data[0]);
  dks::model_t model(msa);

  dks::kernel_weight_t kw{
      {dks::test_kernel_t::partial, 0.25},
      {dks::test_kernel_t::likelihood, 0.25},
      {dks::test_kernel_t::derivative, 0.25},
      {dks::test_kernel_t::pmatrix, 0.25},
  };

  dks::select_kernel(model, msa, kw);
}
