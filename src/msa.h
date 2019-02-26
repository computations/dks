#pragma once
#include <iterator>
#include <pll.h>
#include <string>
#include <vector>

namespace dks {
typedef std::vector<char> sequence_t;
typedef std::string label_t;

class msa_t {
public:
  msa_t() = default;
  msa_t(const pll_msa_t *);
  msa_t(const std::string &);
  void init(const pll_msa_t *msa);
  size_t count() const;
  size_t length() const;
  const char *label(size_t i) const;
  const char *sequence(size_t i) const;
  const pll_state_t *char_map() const;
  bool valid() const;

  double column_entropy() const;

protected:
  std::vector<sequence_t> _sequences;
  std::vector<label_t> _labels;
};

class msa_compressed_t : public msa_t {
public:
  msa_compressed_t(const msa_t &);
  const unsigned int *weights() const;

private:
  std::vector<unsigned int> _weights;
};
} // namespace dks
