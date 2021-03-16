//
// Created by nick on 28-11-19.
//

#include <filesystem>
#include <iostream>
#include "build.h"
#include "file/wave.h"
#include "write.h"

std::map<std::string, std::function<int(std::initializer_list<std::string> l)>> command::build() {
    std::map<std::string, std::function<int(std::initializer_list<std::string> l)>> v{};

    // show audio wave meta data
    auto info = [](std::initializer_list<std::string> l) {
        for (const std::string &i : l) {
            std::cout << i;
            auto r = wave::validate(i, [](wave::file &v) {
                std::cout << v;
            });
            if (r != EXIT_SUCCESS)
                return r;
        }
        return EXIT_SUCCESS;
    };
    v.emplace("i", info);
    v.emplace("I", info);
    v.emplace("info", info);
    v.emplace("-i", info);
    v.emplace("-I", info);
    v.emplace("--info", info);

    // read message from audio wave
    auto read = [](std::initializer_list<std::string> l) {
        for (const std::string &i : l) {
            auto r = wave::validate(i, [](wave::file &v) {
                auto m = wave::read_message(v);
                std::cout << m;
            });
            if (r != EXIT_SUCCESS)
                return r;
        }
        return EXIT_SUCCESS;
    };
    v.emplace("r", read);
    v.emplace("R", read);
    v.emplace("read", read);
    v.emplace("-r", read);
    v.emplace("-R", read);
    v.emplace("--read", read);

    // write message from audio wave
    v.emplace("w", command::write);
    v.emplace("W", command::write);
    v.emplace("write", command::write);
    v.emplace("-w", command::write);
    v.emplace("-W", command::write);
    v.emplace("--write", command::write);

    return v;
}
