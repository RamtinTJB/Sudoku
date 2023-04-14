#ifndef SUDOKU_OPTIONS_H_
#define SUDOKU_OPTIONS_H_

#include <string>
#include <iostream>

struct options {
    bool empty_board = true;
    std::string file_path;
    bool help = false;
    bool error = false;
};

options parse_options(int argc, const char** argv);

std::string help(const char* program);
std::string usage(const char* program);

inline std::ostream& operator<< (std::ostream& os, const options& opt) {
    return os << "Empty Board: " << opt.empty_board << std::endl
        << "File Path: " << opt.file_path << std::endl
        << "Help: " << opt.help << std::endl
        << "Error: " << opt.error << std::endl;
}

#endif
