#ifndef SUDOKU_STRING_UTILS_H_
#define SUDOKU_STRING_UTILS_H_

#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <cstdlib>

inline std::vector<std::string> split_string(std::string s, const std::string& delim) {
    size_t pos;
    std::vector<std::string> output;
    std::string token;
    while ((pos = s.find(delim)) != std::string::npos) {
        token = s.substr(0, pos);
        output.push_back(token);
        s.erase(0, pos + delim.length());
    }
    output.push_back(s);
    return output;
}

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
                }));
}

inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
                }).base(), s.end());
}

inline void trim(std::string& s) {
    rtrim(s);
    ltrim(s);
}

#endif
