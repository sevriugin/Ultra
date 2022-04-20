
#include <sstream>
#include <utility>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "utils.h"

bool isSpace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

int64_t getNumber(std::string &s) {
    using namespace std;

    if (s == "Max") return INT64_MAX;
    if (s == "Min") return INT64_MIN;

    return strtoll(s.data(), nullptr, 10);
}

bool isNumber(std::string &s) {
    using namespace std;

    char* p;
    strtoll(s.c_str(), &p, 10);
    return *p == 0;
}

std::vector<std::string> splitString(std::string &s, const char* separator) {
    using namespace std;
    using namespace boost;

    boost::char_separator<char> sep { separator != nullptr ? separator : " " };
    boost::tokenizer<boost::char_separator<char>> tok(s, sep);

    long number_of_tokens { std::distance(tok.begin(), tok.end()) };
    vector<string> result(number_of_tokens);

    int count {0};
    for(boost::tokenizer<boost::char_separator<char>>::iterator beg = tok.begin(); beg != tok.end(); ++beg)
    {
        std::string token { *beg };
        boost::algorithm::trim_if(token, isSpace);

        result[count++] = token;
    }

    return result;
}

