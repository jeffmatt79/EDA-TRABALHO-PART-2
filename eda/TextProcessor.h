#pragma once
#include <string>
#include <algorithm>
#include <cctype>

class TextProcessor {
public:
    static std::string normalize(const std::string& input) {
        std::string result;
        for (char c : input) {
            if (std::isalnum(c) || c == '-') {
                result += std::tolower(c);
            }
        }
        return result;
    }
};