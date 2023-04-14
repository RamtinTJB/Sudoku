#include <iostream>

#include "game.h"
#include "options.h"

int main(int argc, const char** argv) {
    options opt = parse_options(argc - 1, argv);

    if (opt.help) {
        std::cout << help(argv[0]) << std::endl;
        return 0;
    }

    if (opt.error) {
        std::cout << "Invalid arguments" << std::endl << usage(argv[0]) << std::endl;
        return -1;
    }

    std::cout << opt << std::endl;

    game g(1000, 1000);
    g.loop();

    return 0;
}
