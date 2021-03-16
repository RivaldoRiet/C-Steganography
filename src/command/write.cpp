//
// Created by nick on 28-11-19.
//

#include <iostream>
#include "write.h"
#include "file/wave.h"

int command::write(std::initializer_list<std::string> l) {

    // define file path
    // and text to write
    std::string path{};
    std::string txt{};
    for (const std::string &i : l) {
        path.empty() ? path = i : txt += i;
    }

    // if the argument contains no text then
    // ask for text to save in wave file
    while (txt.empty()) {
        std::cout << "Insert text:\n";
        std::cin >> txt;
    }

    std::cout << "File: \t\t" << path << "\nMessage: \t" << txt << std::endl;

    // TODO: Write message to file
    // omdat intel little endian is
    // is de minst signifikante waarde aan het begin
    // de minst signifikante waarde moeten we vervangen
    // daar komt onze letter
    // herhaal elk blok
    // tot de null waarde

    return EXIT_SUCCESS;
}
