#pragma once

#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <regex>


bool check(const std::string &value) {
    static const std::regex CHECK_PATTERN("[^{}]*(\\{\\d+\\}[^{}]*)*");
    return std::regex_match(value, CHECK_PATTERN);
}

template<class T>
std::string to_string(T &&t) {
    std::ostringstream out;
    out << t;
    return out.str();
}

std::string parse(const std::string &s, std::vector <std::string> &replacements) {
    static const std::regex PARTS_PATTERN("([^{}]+)|(\\{\\d+\\})");
    std::string res = "";
    std::string cur_part;
    auto parts_begin = std::sregex_iterator(s.begin(), s.end(), PARTS_PATTERN);
    auto parts_end = std::sregex_iterator();
    long number;
    for (auto i = parts_begin; i != parts_end; ++i) {
        cur_part = i->str();
        if (cur_part[0] == '{') {
            try {
                number = std::stol(cur_part.substr(1, cur_part.length() - 2));
            } catch (std::exception &e) {
                throw std::runtime_error("error");
            }
            if (number < 0 || number >= replacements.size())
                throw std::runtime_error("error");
            res += replacements[number];
        } else
            res += cur_part;
    }
    return res;
}

template<class... Args>
std::string format(const std::string &s, Args &&... args) {
    if (!check(s))
        throw std::runtime_error("error");
    std::vector <std::string> replacements{ to_string(std::forward<Args>(args))... };
    return parse(s, replacements);
}