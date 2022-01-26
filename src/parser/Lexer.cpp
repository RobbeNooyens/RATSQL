//
// Created by Maarten on 28/11/2021.
//

#include <algorithm>
#include <iostream>

#include "Lexer.h"
#include "UndefinedTokenException.h"

Lexer::Lexer(const map<string, string> &m, const vector<vector<string>> &a) : tokenMap(m), aliases(a) {}

vector<string> Lexer::splitString(const string &parseString) {
    // String that needs to be parsed
    string stringCopy = parseString;
    // List of substrings
    vector<string> stringToTokens;
    for (int i = 0; i < stringCopy.size(); ++i) {
        string w;
        w += stringCopy[i];
        if (stringCopy[i] == delimiter) { // Check if the end of a word has been reached
            if (i != 0) {
                // Make a substring and place it in the list of substrings
                string substr = stringCopy.substr(0, i);
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
                    string substr = stringCopy.substr(0, i);
                    stringToTokens.emplace_back(substr);
                }
                // Make a substring and place it in the list of substrings
                string substr = stringCopy.substr(i, k);
                stringToTokens.emplace_back(substr);
                // Remove the substring from the string that needs to be parsed still
                stringCopy.erase(stringCopy.begin(), stringCopy.begin() + i + k);
                i = -1;
            }
        }
    }
    // Add any possible remainings
    if (!stringCopy.empty()) {
        stringToTokens.emplace_back(stringCopy);
    }
    return stringToTokens;
}

// Todo: nakijken
unsigned int Lexer::isDelimiter(const string &s, unsigned int offset) {
    int k = 0;
    for (const auto &name : aliases) {
        for (const auto &n : name) {
            string temp;
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
                k = max(k, j);
            }
        }
    }
    return k;
}

vector<ParseToken> Lexer::tokenise(const vector<string> &v) {
    vector<ParseToken> t;
    for (auto &entry : v) {
        string token;
        /*if (isString(entry)) {
            token = "STRING";
        } else */if (tokenMap.find(entry) != tokenMap.end()) {
            token = tokenMap[entry];
        } else if (isNumber(entry)) {
            token = "DIGIT";
        } else if (isName(entry)){
            token = "NAME";
        } else {
            string k (entry.begin(), entry.end());
            throw UndefinedTokenException(k);
        }
        t.emplace_back(ParseToken(token, entry));
    }
    return t;
}

bool Lexer::isString(const string &s) {
    // A part of the input is considered a string when it starts and ends with a string delimiter
    int lastChar = s.size() - 1;
    for (auto &delimiter : {'"', '\''}) {
        if (s[0] == delimiter and s[lastChar] == delimiter) {
            return true;
        }
    }
    return false;
}

bool Lexer::isNumber(const string &s) {
    // None of the characters in the string can be anything other than a digit or a dot
    if (std::all_of(s.begin(), s.end(), [&](char c) { return isdigit(c) or c == '.';})) {
        return true;
    } else {
        return false;
    }
}

bool Lexer::isName(const string &s) {
    // All characters in the string should be alphanumeric, the first one should be alpha
    if (isalpha(s[0]) and all_of(s.begin()+1, s.end(), [&](char c) { return isalnum(c);})) {
        return true;
    } else {
        return false;
    }
}

vector<ParseToken> Lexer::tokenise(const string &s) {
    return tokenise(splitString(s));
}

Lexer::Lexer(): tokenMap(), aliases() {}
