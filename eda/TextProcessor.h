#pragma once
#include <string>
#include <algorithm>
#include <cctype>

#include <string>
#include <unordered_map>
#include <cctype>

class TextProcessor {
public:
    static std::string normalize(const std::string& input) {
       
        static const std::unordered_map<char, char> accent_map = {
            {'á', 'a'}, {'à', 'a'}, {'ã', 'a'}, {'â', 'a'}, {'ä', 'a'},
            {'é', 'e'}, {'è', 'e'}, {'ê', 'e'}, {'ë', 'e'},
            {'í', 'i'}, {'ì', 'i'}, {'î', 'i'}, {'ï', 'i'},
            {'ó', 'o'}, {'ò', 'o'}, {'õ', 'o'}, {'ô', 'o'}, {'ö', 'o'},
            {'ú', 'u'}, {'ù', 'u'}, {'û', 'u'}, {'ü', 'u'},
            {'ç', 'c'},
            {'Á', 'a'}, {'À', 'a'}, {'Ã', 'a'}, {'Â', 'a'}, {'Ä', 'a'},
            {'É', 'e'}, {'È', 'e'}, {'Ê', 'e'}, {'Ë', 'e'},
            {'Í', 'i'}, {'Ì', 'i'}, {'Î', 'i'}, {'Ï', 'i'},
            {'Ó', 'o'}, {'Ò', 'o'}, {'Õ', 'o'}, {'Ô', 'o'}, {'Ö', 'o'},
            {'Ú', 'u'}, {'Ù', 'u'}, {'Û', 'u'}, {'Ü', 'u'},
            {'Ç', 'c'}
        };

        std::string result;
        for (unsigned char c : input) {
            // se tem no mapa, substitui
            if (accent_map.count(c)) {
                result += accent_map.at(c);
            }
            else if (std::isalnum(c) || c == '-') {
                result += std::tolower(c);
            }
            // ignora outros caracteres
        }
        return result;
    }
};
