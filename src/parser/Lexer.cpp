//
// Created by Maarten on 28/11/2021.
//

#include <algorithm>
#include <iostream>

#include "Lexer.h"
#include "UndefinedTokenException.h"

Lexer::Lexer(const wstring &parseString): tokenMap(generateTokenMap()) {
    try {
        tokenise(splitString(parseString));
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}

vector<wstring> Lexer::splitString(const wstring &parseString) {
    // String that needs to be parsed
    wstring stringCopy = parseString;
    // List of substrings
    vector<wstring> stringToTokens;
    for (int i = 0; i < stringCopy.size(); ++i) {
        if (stringCopy[i] == delimiter) { // Check if the end of a word has been reached
            // Make a substring and place it in the list of substrings
            wstring substr = stringCopy.substr(0, i);
            stringToTokens.emplace_back(substr);
            // Remove the substring from the string that needs to be parsed still
            stringCopy.erase(stringCopy.begin(), stringCopy.begin() + i+1);
            i = 0;
        } else { // Todo: nakijken
            // Check for a match with any other delimiter
            unsigned int k = isDelimiter(stringCopy);
            if (k) {
                // Make a substring and place it in the list of substrings
                wstring substr = stringCopy.substr(0, k);
                stringToTokens.emplace_back(substr);
                // Remove the substring from the string that needs to be parsed still
                stringCopy.erase(stringCopy.begin(), stringCopy.begin() + k +1);
                i = 0;
            }
        }
    }
    stringToTokens.emplace_back(stringCopy);
    return stringToTokens;
}

// Todo: nakijken
unsigned int Lexer::isDelimiter(const wstring &s) {
    for (const auto &name : names) {
        for (const auto &n : name) {
            wstring temp;
            int j = 0;
            temp += s[j];
            while (temp.size() < n.size()) {
                if (n[j] != s[j]) {
                    break;
                } else {
                    temp += s[++j];
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
        if (isString(entry)) {
            token = STRING;
        } else if (tokenMap.find(entry) != tokenMap.end()) {
            token = tokenMap[entry];
        } else if (isNumber(entry)) {
            token = NUMBER;
        } else if (isName(entry)){
            token = NAME;
        } else {
            string k (entry.begin(), entry.end());
            throw UndefinedTokenException(k);
        }
        t.emplace_back(Token(token, entry));
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
