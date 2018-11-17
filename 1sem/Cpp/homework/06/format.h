#pragma once

#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <regex>

bool check(const std::string &value) {
    return std::regex_match(value, std::regex("[^{}]*(\\{\\d+\\}[^{}]*)*"));
}

template<class T>
std::string to_string(T &t) {
    std::ostringstream out;
    out << t;
    return out.str();
}

std::string parse(const std::string &s, std::vector <std::string> &replacements) {
    std::string res = "";
    std::string cur_part;
    std::regex parts("([^{}]+)|(\\{\\d+\\})");
    auto parts_begin = std::sregex_iterator(s.begin(), s.end(), parts);
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

template<class T, class... Args>
std::string parse(const std::string &s, std::vector <std::string> &replacements, T &&t, Args &&... args) {
    replacements.push_back(to_string(t));
    return parse(s, replacements, std::forward<Args>(args)...);
}

template<class... Args>
std::string format(const std::string &s, Args &&... args) {
    if (!check(s))
        throw std::runtime_error("error");
    std::vector <std::string> replacements;
    return parse(s, replacements, std::forward<Args>(args)...);
}