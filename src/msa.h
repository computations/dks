#pragma once
#include <string>
#include <vector>
#include <pll.h>

typedef std::vector<char> sequence_t;
typedef char* label_t;

class msa_t{
public:
    msa_t() = default;
    msa_t(const pll_msa_t*);
    size_t count();
    size_t width();
    char* label(size_t i);
private:
    std::vector<sequence_t> _sequences;
    std::vector<label_t> _labels;
};
