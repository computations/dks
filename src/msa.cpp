#include "msa.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace dks {
msa_t::msa_t(const pll_msa_t *msa) { init(msa); }

msa_t::msa_t(const std::string &filename) {
  if (pll_phylip_t *fd = pll_phylip_open(filename.c_str(), pll_map_phylip)) {
    pll_msa_t *pll_msa = nullptr;
    if ((pll_msa = pll_phylip_parse_interleaved(fd)) ||
        (pll_msa = pll_phylip_parse_sequential(fd))) {
      init(pll_msa);
      pll_msa_destroy(pll_msa);
      pll_phylip_close(fd);
      return;
    } else {
      pll_phylip_close(fd);
    }
  }
  if (pll_fasta_t *fd = pll_fasta_open(filename.c_str(), pll_map_fasta)) {
    char *header = nullptr;
    char *sequence = nullptr;
    long sequence_len = 0;
    long header_len = 0;
    long sequence_number = 0;
    long expected_sequence_length = 0;

    while (pll_fasta_getnext(fd, &header, &header_len, &sequence, &sequence_len,
                             &sequence_number)) {
      if (expected_sequence_length == 0) {
        expected_sequence_length = sequence_len;
      } else if (expected_sequence_length != sequence_len) {
        throw std::runtime_error("Sequences don't match in size");
      }
      _sequences.emplace_back(sequence, sequence + sequence_len);
      free(sequence);
      _labels.emplace_back(header);
      free(header);
    }
    pll_fasta_close(fd);
  }
  if (!valid()){
      throw std::runtime_error("failed to parse the msa file");
  }
}

void msa_t::init(const pll_msa_t *msa) {
  for (int i = 0; i < msa->count; i++) {
    _labels.emplace_back(msa->label[i]);
    _sequences.emplace_back(msa->sequence[i], msa->sequence[i] + msa->length);
  }
}

size_t msa_t::count() const { return _labels.size(); }

size_t msa_t::length() const {
  if (_sequences.empty()) {
    return 0;
  }
  return _sequences.front().size();
}

const char *msa_t::label(size_t i) const { return _labels[i].data(); }

const char *msa_t::sequence(size_t i) const { return _sequences[i].data(); }

const pll_state_t *msa_t::char_map() const { return pll_map_nt; }

bool msa_t::valid() const {
    return _sequences.size() > 0;
}

msa_compressed_t::msa_compressed_t(const msa_t &msa) {
  char **tmp_sequences = (char **)malloc(msa.count() * sizeof(char *));
  for (size_t i = 0; i < msa.count(); i++) {
    tmp_sequences[i] = (char *)malloc(msa.length() * sizeof(char));
    for (size_t j = 0; j < msa.length(); j++) {
      tmp_sequences[i][j] = msa.sequence(i)[j];
    }
  }

  int tmp_length = msa.length();
  unsigned int *tmp_weights = pll_compress_site_patterns(
      tmp_sequences, msa.char_map(), msa.count(), &tmp_length);

  _weights = std::vector<unsigned int>(tmp_weights, tmp_weights + tmp_length);

  for (size_t i = 0; i < msa.count(); i++) {
    _sequences.emplace_back(
        sequence_t(tmp_sequences[i], tmp_sequences[i] + tmp_length));

    _labels.emplace_back(msa.label(i));
  }

  free(tmp_weights);

  for (size_t i = 0; i < msa.count(); i++) {
    free(tmp_sequences[i]);
  }
  free(tmp_sequences);
}

const unsigned int *msa_compressed_t::weights() const {
  return _weights.data();
}
} // namespace dks
