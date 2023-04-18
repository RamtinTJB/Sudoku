#ifndef SUDOKU_OPTIONS_H_
#define SUDOKU_OPTIONS_H_

#include <string>
#include <iostream>

struct options {
    std::string file_path;
    bool from_file = false;
    bool from_image = false;
    bool help = false;
    bool error = false;
};

options parse_options(int argc, const char** argv);

std::string help(const char* program);
std::string usage(const char* program);

inline std::ostream& operator<< (std::ostream& os, const options& opt) {
    return os << "From File: " << opt.from_file << std::endl
        << "From Image: " << opt.from_image << std::endl
        << "File Path: " << opt.file_path << std::endl
        << "Help: " << opt.help << std::endl
        << "Error: " << opt.error << std::endl;
}

#endif
