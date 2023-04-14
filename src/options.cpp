#include "options.h"

#include <string>
#include <cstring>

std::string usage(const char* program) {
    return std::string(program) + " [-h] -f <file name>";
}

std::string help(const char* program) {
    return usage(program) + "\n" +
        "Options:\n" +
        "\t-h Optional. Show this text and exit.\n\n" +
        "\t-f Optional. File name containing a sudoku board. If ommited, the program will start with an empty sudoku board.";
}

options parse_options(int argc, const char** argv) {
    options opt;
    int counter = 1;

    while (counter <= argc) {
        if (strcmp(argv[counter], "-h") == 0) {
            opt.help = true;
        } else if (strcmp(argv[counter], "-f") == 0) {
            counter++;
            opt.empty_board = false;
            if (counter <= argc) {
                opt.file_path = std::string(argv[counter]);
            } else {
                opt.error = true;
            }
        } else {
            opt.error = true;
        }
        counter++;
    }

    return opt;
}
