#pragma once
#include <string>
#include <vector>
#include <pll.h>

typedef std::vector<char> sequence_t;
typedef std::string label_t;

class msa_t{
public:
    msa_t(const pll_msa_t*);
    size_t count();
    size_t width();
private:
    std::vector<sequence_t> _sequences;
    std::vector<label_t> _labels;
};
