#include "msa.h"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace dks{

    size_t strlen(char* s){
        int i = 0;
        while(true){
            if (!s[i]){return i+1;}
            i++;
        }
    }


    msa_t::msa_t(const pll_msa_t* msa){
        init(msa);
        _states = 4;
    }

    msa_t::msa_t(const std::string& filename){
        if(pll_phylip_t* fd = pll_phylip_open(filename.c_str(), pll_map_phylip)){
            pll_msa_t* pll_msa = nullptr;
            if ((pll_msa = pll_phylip_parse_interleaved(fd)) ||
                (pll_msa = pll_phylip_parse_sequential(fd))) {
                init(pll_msa);
                pll_msa_destroy(pll_msa);
                pll_phylip_close(fd);
                return;
            }else {
                pll_phylip_close(fd);
            }
        }
        if(pll_fasta_t* fd = pll_fasta_open(filename.c_str(), pll_map_fasta)){
            char *header = nullptr;
            char *sequence = nullptr;
            long sequence_len = 0;
            long header_len = 0;
            long sequence_number = 0;
            long expected_sequence_length = 0;

            while(pll_fasta_getnext(fd, &header, &header_len, &sequence,
                        &sequence_len, &sequence_number)){
                if(expected_sequence_length == 0){
                    expected_sequence_length = sequence_len;
                }
                else if (expected_sequence_length != sequence_len){
                    //for(auto l : _labels) {
                        //free(l);
                    //}
                    throw std::runtime_error("Sequences don't match in size");
                }
                _sequences.emplace_back(sequence, sequence + sequence_len);
                free(sequence);
                _labels.push_back(header);
            }
            pll_fasta_close(fd);
        }
    }

    msa_t::~msa_t(){
        for (auto c : _labels){
            free(c);
        }
    }

    void msa_t::init(const pll_msa_t* msa){
        for (int i = 0; i < msa->count; i++) {
            size_t label_size = strlen(msa->label[i]);
            _labels.emplace_back((char*) malloc(sizeof(char) * label_size));
            memcpy(_labels[i], msa->label[i], label_size);
            _sequences.emplace_back(msa->sequence[i],
                                    msa->sequence[i] + msa->length);
        }
    }

    size_t msa_t::count() const{
        return _labels.size();
    }

    size_t msa_t::length() const{
        if (_sequences.empty()){return 0;}
        return _sequences.front().size();
    }

    size_t msa_t::states() const{
        return 4;
    }

    const char* msa_t::label(size_t i) const{
        return _labels[i];
    }

    const char* msa_t::sequence(size_t i) const{
        return _sequences[i].data();
    }

    const pll_state_t* msa_t::char_map() const{
        return pll_map_nt;
    }
}
