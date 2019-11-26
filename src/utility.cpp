#include "utility.hpp"

std::vector<string> Utility::split_str(const std::string& str, char delim = ' ') {
    auto cont = std::vector<string>();
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
    return cont;
}