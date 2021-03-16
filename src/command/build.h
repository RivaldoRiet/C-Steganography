//
// Created by nick on 28-11-19.
//

#ifndef SECRET_MESSAGE_BUILD_H
#define SECRET_MESSAGE_BUILD_H


#include <map>
#include <string>
#include <functional>

namespace command {
    std::map<std::string, std::function<int(std::initializer_list<std::string> l)>> build();
};


#endif //SECRET_MESSAGE_BUILD_H
