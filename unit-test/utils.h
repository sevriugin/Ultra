#ifndef CHALLENGE_UTILS_H
#define CHALLENGE_UTILS_H

#include <stdexcept>

bool isSpace(char c);

int64_t getNumber(std::string &s);

bool isNumber(std::string &s);

std::vector<std::string> splitString(std::string &s, const char* separator);

#endif //CHALLENGE_UTILS_H
