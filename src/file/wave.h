//
// Created by nick on 28-11-19.
//

#ifndef SECRET_MESSAGE_META_H
#define SECRET_MESSAGE_META_H


#include <iostream>
#include <fstream>
#include <string>
#include <functional>

namespace wave {
    struct fmt {
        int size{}; // int32_t
        off_t pos{};

        // meta data
        unsigned short int format_code{};
        unsigned short int channel{};
        long sample_rate{};
        long bytes_per_sec{};
        unsigned short bytes_per_sample{};
        unsigned short bits_per_sample{};
        long data_chunk{};
        long length_chunk{};

        friend std::ostream &operator<<(std::ostream &out, const fmt &v);
    };

    struct data {
        int size{};
        off_t pos{};

        friend std::ostream &operator<<(std::ostream &out, const data &v);
    };

    struct file {
        std::string path{};
        int riff{};
        fmt meta_data{};
        data audio_data{};

        friend std::ostream &operator<<(std::ostream &out, const file &v);
    };

    file build(const std::string &path);

    void meta_data(file &v);

    std::string read_message(const file &v);

    void write_message(file &v);

    int validate(const std::string &path, const std::function<void(file &v)> &func);
}


#endif //SECRET_MESSAGE_META_H
