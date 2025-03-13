#pragma once
#include <string>
#include <vector>

template <typename T=std::string>
static std::vector<T>* deserialize(const std::string& source,
                                   char separator,
                                   T (*converter)(const std::string&) = [](const std::string& x) { return x; }) {
    int prev = 0;
    std::vector<T>* result = new std::vector<T>();
    for (int curr = 0; curr < source.length(); ++curr) {
        if (source[curr] == separator) result->push_back(converter(source.substr(prev, curr - prev + 1)));
        prev = curr + 1;
    }
    if (prev < source.length()) result->push_back(converter(source.substr(prev, source.length() - prev + 1)));
    return result;
}

template <typename T>
static std::string serialize(const std::vector<T>& vals,
                             const char separator,
                             std::string (*converter)(const T&) = [](const T& val) { return val; }) {
    std::string result;
    for (const T& val : vals) {
        if (!result.empty()) result += separator;
        result += converter(val);
    }
    return result;
}