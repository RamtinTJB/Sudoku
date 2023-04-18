#include "options.h"

#include <string>
#include <cstring>

std::string usage(const char* program) {
    return std::string(program) + " [-h] [-f, -i] <file name>";
}

std::string help(const char* program) {
    return usage(program) + "\n" +
        "Options:\n" +
        "\t-h Optional. Show this text and exit.\n\n" +
        "\t-f Optional. File name containing a sudoku board.\n" +
        "\t-i Optional. Load Sudoku from an image. If neither -f or -i are provided, an empty board will be loaded.";
}

options parse_options(int argc, const char** argv) {
    options opt;
    int counter = 1;

    while (counter <= argc) {
        if (strcmp(argv[counter], "-h") == 0) {
            opt.help = true;
        } else if (strcmp(argv[counter], "-f") == 0) {
            counter++;
            opt.from_file = true;
            if (counter <= argc) {
                opt.file_path = std::string(argv[counter]);
            } else {
                opt.error = true;
            }
        } else if (strcmp(argv[counter], "-i") == 0) {
            counter++;
            opt.from_image = true;
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

    if (opt.from_file && opt.from_image) opt.error = true;

    return opt;
}
