//
// Created by nick on 28-11-19.
//

#include <string>
#include <sstream>
#include <filesystem>
#include "wave.h"
#include "read.h"

namespace wave {
    std::ostream &operator<<(std::ostream &out, const fmt &v) {
        out << "FMT (Format or meta data): " << "\tsize: " << v.size;

        // meta data
        out << "\tformat code: " << v.format_code;
        out << "\tChannel: " << v.channel;
        out << "\tSample Rate: " << v.sample_rate;
        out << "\tBytes per sec: " << v.bytes_per_sec;
        out << "\tBytes Per Sample: " << v.bytes_per_sample;
        out << "\tBits per sample: " << v.bits_per_sample;
        out << "\tData chuck: " << v.data_chunk;
        out << "\tLength of chunk: " << v.length_chunk;

        return out;
    }

    std::ostream &operator<<(std::ostream &out, const data &v) {
        out << "DATA (audio): " << "\t size: " << v.size;
        return out;
    }

    std::ostream &operator<<(std::ostream &out, const file &v) {
        out << "\nRIFF (file size): " << v.riff << "\n" << v.meta_data << "\n" << v.audio_data << "\n";
        return out;
    }

    file build(const std::string &path) {
        std::ifstream stream(path, std::ios::binary); // stream
        file f{path};
        do {
            // data block name
            // read 4 bytes and cast it to a string
            std::string id = read::read_chunk_id(stream);

            // RIFF block
            if (id == "RIFF") {
                f.riff = read::read_int(stream); // read 8 bytes to int30_t (RIFF or Total file size)
            }

            // FMT block
            if (id == "fmt ") {
                f.meta_data.size = read::read_int(stream); // read 8 bytes to int30_t (FMT or block size)
                f.meta_data.pos = stream.tellg(); // save the position so that I can return to that point
            }

            // data block
            if (id == "data") {
                f.audio_data.size = read::read_int(stream); // read 8 bytes to int30_t (FMT or block size)
                f.audio_data.pos = stream.tellg(); // save the position so that I can return to that point
            }
        } while (!f.riff || !f.meta_data.size || !f.audio_data.size);
        stream.close();
        return f;
    }

    void meta_data(file &v) {
        FILE *stream = fopen(v.path.c_str(), "rb"); // stream
        fseek(stream, v.meta_data.pos, SEEK_SET);

        fread((unsigned short int *) &v.meta_data.format_code, 2, 1, stream);
        fread((unsigned short int *) &v.meta_data.channel, 2, 1, stream);
        fread((long *) &v.meta_data.sample_rate, 4, 1, stream);
        fread((long *) &v.meta_data.bytes_per_sec, 4, 1, stream);
        fread((unsigned short int *) &v.meta_data.bytes_per_sample, 2, 1, stream);
        fread((unsigned short int *) &v.meta_data.bits_per_sample, 2, 1, stream);
        fread((long *) &v.meta_data.data_chunk, 4, 1, stream);
        fread((long *) &v.meta_data.length_chunk, 4, 1, stream);

        fclose(stream);
    }

    std::string read_message(const file &v) {
        std::ifstream stream(v.path, std::ios::binary | std::ios::in | std::ios::out); // stream
        stream.seekg(v.audio_data.pos); // go to data position 44)

        std::string message{};
        std::string file_bits{};

        auto i = 0;
        auto count = 0;
        bool end_of_message = false;

        while (stream.good() && !end_of_message) {
            if (count == 8) {
                message.clear();
                end_of_message = read::validate_bits(file_bits, message);
                count = 0;
            }
            stream.read(reinterpret_cast<char *>(&i), 2);
            file_bits += std::to_string(i & 1);

            ++count;
        }

        stream.close();
        return message;
    }

    void write_message(file &v) {

    }

    int validate(const std::string &path, const std::function<void(file &v)> &func) {
        // filename or path
        if (!std::filesystem::exists(path)) {
            std::cerr << "File does not exists\n";
            return EXIT_FAILURE;
        }

        // valid wave file
        auto wave = wave::build(path);
        wave::meta_data(wave);
        if (wave.meta_data.format_code != 1 || wave.meta_data.bits_per_sample < 16) {
            std::cerr << "file is to small or compressed";
            return EXIT_FAILURE;
        }

        func(wave);
        return EXIT_SUCCESS;
    }
}
