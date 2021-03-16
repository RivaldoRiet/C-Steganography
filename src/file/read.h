//
// Created by nick on 08-01-20.
//

#ifndef SECRET_MESSAGE_READ_H
#define SECRET_MESSAGE_READ_H


#include <string>
#include <fstream>
#include <bitset>

namespace read {
    std::string read_chunk_id(std::ifstream &stream) {
        char buff[4]{};
        stream.read(buff, 4);
        return {buff, 4};
    }

    int32_t read_int(std::ifstream &stream) {
        int32_t buff{};
        stream.read(reinterpret_cast<char *>(&buff), sizeof(buff));
        return buff;
    }

    bool validate_bits(std::string &file_bits, std::string &message) {
        bool end_of_message = false;
        std::stringstream in(file_bits);
        std::bitset<8> bs;
        while (in >> bs) {
            const auto ascii = bs.to_ullong();
            const auto character = static_cast<char>(ascii);
            end_of_message = (character == '\0');
            message += character; // Uiteindelijk ontcijferd bericht
        }
        return end_of_message;
    }
};


#endif //SECRET_MESSAGE_READ_H
