#pragma once
#include <string>
#include <vector>
#include <iterator>
#include <pll.h>

namespace dks{
    typedef std::vector<char> sequence_t;
    typedef char* label_t;

    class msa_t{
    public:
        msa_t() = default;
        msa_t(const pll_msa_t*);
        size_t count() const;
        size_t length() const;
        size_t states() const;
        char* label(size_t i);
        const char* sequence(size_t i) const;
        const pll_state_t* char_map() const;
    private:
        std::vector<sequence_t> _sequences;
        std::vector<label_t> _labels;
        unsigned int _states;
    };
}
