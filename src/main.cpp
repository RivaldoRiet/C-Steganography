
#include <iostream>
#include "command/build.h"
#include "tool/arch.h"
#include "tool/range_to_initializer_list.h"

int main(int argc, char **argv) {
    // help summary
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [R/w/i] <FILE>\n";
        return EXIT_SUCCESS;
    }

    // little endian architecture
    if (arch::cur_byte_order() == arch::endian::big_endian) {
        std::cerr << "Only little endian machines supported\n";
        return EXIT_FAILURE;
    }

    // commands
    std::string option{"read"};
    auto commands = command::build();
    if (commands.find(argv[1]) != commands.end()) {
        option = argv[1];
    }

    // convert args array to vector
    // and convert the vector to a init list
    // and run the command
    std::vector<std::string> vec(argv + (argc > 2 ? 2 : 1), argv + argc);
    return commands[option](range_to_initializer_list(vec.begin(), vec.end()));
}
