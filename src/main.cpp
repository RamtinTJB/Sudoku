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

    game g(1000, 1000);
    if (!opt.empty_board) {
        g.load_from_file(opt.file_path);
    }
    g.loop();

    return 0;
}
