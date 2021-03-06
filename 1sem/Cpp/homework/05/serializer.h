
#pragma once

#include <iostream>
#include <type_traits>
#include <sstream>

enum class Error {
    NoError,
    CorruptedArchive
};

//**********************************************************************************************
//                              Serializer
//**********************************************************************************************

class Serializer {
private:
    static constexpr char Separator = ' ';
    std::ostream &output;

public:
    explicit Serializer(std::ostream &out)
            : output(out) {}

    template<class T>
    Error save(T &object);

    template<class... Args>
    Error operator()(Args &&... args);

private:
    Error save(bool val);

    Error save(uint64_t val);

    template<class T, class... Args>
    Error process(T &&val, Args &&... args);

    template<class T>
    Error process(T &&val);
};

template<class T>
Error Serializer::save(T &object) {
    return object.serialize(*this);
}

template<class... Args>
Error Serializer::operator()(Args &&... args) {
    return process(std::forward<Args>(args)...);
}

Error Serializer::save(bool val) {
    output << (val ? "true" : "false");
    return Error::NoError;
}

Error Serializer::save(uint64_t val) {
    output << val;
    return Error::NoError;
}

template<class T, class... Args>
Error Serializer::process(T &&val, Args &&... args) {
    Error err_code = save(val);
    if (err_code != Error::NoError)
        return err_code;
    output << Separator;
    return process(std::forward<Args>(args)...);
}

template<class T>
Error Serializer::process(T &&val) {
    return save(val);
}

//**********************************************************************************************
//                              Deserializer
//**********************************************************************************************

class Deserializer {
private:
    std::istream &input;

public:
    explicit Deserializer(std::istream &in)
            : input(in) {}

    template<class T>
    Error load(T &object);

    template<class... Args>
    Error operator()(Args &&... args);

private:
    Error load(bool &val);

    Error load(uint64_t &val);

    template<class T, class... Args>
    Error process(T &&val, Args &&... args);

    template<class T>
    Error process(T &&val);
};

template<class T>
Error Deserializer::load(T &object) {
    return object.serialize(*this);
}

template<class... Args>
Error Deserializer::operator()(Args &&... args) {
    return process(std::forward<Args>(args)...);
}

Error Deserializer::load(bool &val) {
    std::string s_val;
    input >> s_val;
    if (s_val == "true") {
        val = true;
    } else if (s_val == "false") {
        val = false;
    } else {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

Error Deserializer::load(uint64_t &val) {
    std::string s_val;
    input >> s_val;
    if (s_val.length() == 0 || s_val[0] == '-')
        return Error::CorruptedArchive;
    size_t pos;
    try {
        val = std::stoull(s_val, &pos);
    } catch (std::exception &e) {
        return Error::CorruptedArchive;
    }
    if (pos != s_val.size())
        return Error::CorruptedArchive;
    return Error::NoError;
}

template<class T, class... Args>
Error Deserializer::process(T &&val, Args &&... args) {
    Error err_code = load(val);
    if (err_code != Error::NoError)
        return err_code;
    return process(std::forward<Args>(args)...);
}

template<class T>
Error Deserializer::process(T &&val) {
    return load(val);
}
