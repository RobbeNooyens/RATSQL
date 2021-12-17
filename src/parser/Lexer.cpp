//
// Created by Maarten on 28/11/2021.
//

#include <algorithm>
#include <iostream>

#include "Lexer.h"
#include "UndefinedTokenException.h"

Lexer::Lexer() : tokenMap(generateTokenMap()) {}

vector<wstring> Lexer::splitString(const wstring &parseString) {
    // String that needs to be parsed
    wstring stringCopy = parseString;
    // List of substrings
    vector<wstring> stringToTokens;
    for (int i = 0; i < stringCopy.size(); ++i) {
        wstring w;
        w += stringCopy[i];
        if (stringCopy[i] == delimiter) { // Check if the end of a word has been reached
            if (i != 0) {
                // Make a substring and place it in the list of substrings
                wstring substr = stringCopy.substr(0, i);
                stringToTokens.emplace_back(substr);
            }
            // Remove the substring from the string that needs to be parsed still
            stringCopy.erase(stringCopy.begin(), stringCopy.begin() + i+1);
            i = -1;
        } else { // Todo: nakijken
            // Check for a match with any other delimiter
            unsigned int k = isDelimiter(stringCopy, i);
            if (k) {
                // Check for any offset, if a delimiter is found, the previous substring should also be saved
                if (i > 0) {
                    wstring substr = stringCopy.substr(0, i);
                    stringToTokens.emplace_back(substr);
                }
                // Make a substring and place it in the list of substrings
                wstring substr = stringCopy.substr(i, k);
                stringToTokens.emplace_back(substr);
                // Remove the substring from the string that needs to be parsed still
                stringCopy.erase(stringCopy.begin(), stringCopy.begin() + i + k);
                i = -1;
            }
        }
    }
    return stringToTokens;
}

// Todo: nakijken
unsigned int Lexer::isDelimiter(const wstring &s, unsigned int offset) {
    for (const auto &name : names) {
        for (const auto &n : name) {
            wstring temp;
            int j = 1;
            temp += s[offset + j - 1];
            while (temp.size() < n.size()) {
                if (n[j - 1] != s[offset + j - 1]) {
                    break;
                } else {
                    temp += s[offset + ++j - 1];
                }
            }
            if (n == temp) {
                return j;
            }
        }
    }
    return 0;
}

vector<Token> Lexer::tokenise(const vector<wstring> &v) {
    vector<Token> t;
    for (auto &entry : v) {
        TokenTypes token;
        // Make a normal string from the wstring entry
        string content (entry.begin(), entry.end());
        if (isString(entry)) {
            token = STRING;
        } else if (tokenMap.find(entry) != tokenMap.end()) {
            token = tokenMap[entry];
            content = wStringToString[token];
        } else if (isNumber(entry)) {
            token = NUMBER;
        } else if (isName(entry)){
            token = NAME;
        } else {
            string k (entry.begin(), entry.end());
            throw UndefinedTokenException(k);
        }
        t.emplace_back(Token(token, content));
    }
    return t;
}

bool Lexer::isString(const wstring &s) {
    // A part of the input is considered a string when it starts and ends with a string delimiter
    int lastChar = s.size() - 1;
    for (auto &delimiter : {'"', '\''}) {
        if (s[0] == delimiter and s[lastChar] == delimiter) {
            return true;
        }
    }
    return false;
}

bool Lexer::isNumber(const wstring &s) {
    // None of the characters in the string can be anything other than a digit or a dot
    if (std::all_of(s.begin(), s.end(), [&](char c) { return isdigit(c) or c == '.';})) {
        return true;
    } else {
        return false;
    }
}

bool Lexer::isName(const wstring &s) {
    // All characters in the string should be alphanumeric, the first one should be alpha
    if (isalpha(s[0]) and all_of(s.begin()+1, s.end(), [&](char c) { return isalnum(c);})) {
        return true;
    } else {
        return false;
    }
}

vector<Token> Lexer::tokenise(const wstring &s) {
    return tokenise(splitString(s));
}
