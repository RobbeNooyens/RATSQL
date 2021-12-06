//
// Created by Maarten on 28/11/2021.
//

#include "RelaxParser.h"

RelaxParser::RelaxParser(const std::string &parseString) {

}

std::vector<std::string> RelaxParser::splitString(const std::string &parseString) {
    // String that needs to be parsed
    std::string stringCopy = parseString;
    // List of substrings
    std::vector<std::string> stringToTokens;
    for (int i = 0; i < stringCopy.size(); ++i) {
        if (stringCopy[i] == delimiter) { // Check if the end of a word has been reached
            // Make a substring and place it in the list of substrings
            std::string substr = stringCopy.substr(0, i);
            stringToTokens.emplace_back(substr);
            // Remove the substring from the string that needs to be parsed still
            stringCopy.erase(stringCopy.begin(), stringCopy.begin() + i+1);
            i = 0;
        }
    }
    return stringToTokens;
}
