//
// Created by Maarten on 28/11/2021.
//

#ifndef RATSQL_LEXER_H
#define RATSQL_LEXER_H

#include "ParseTemplate.h"

#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

class CFG;
/**
 * @class Lexer
 * @brief Class implemented for Lexer, reading and lexing the input
 */
class Lexer {
private:
    /// @brief char - delimiter used to split the given strings
    const char delimiter = ' ';
    /// @brief std::map<std::string, std::string> - tokenmap
    map<string, string> tokenMap;
    /// @brief std::vector<std::vector<std::string>> - aliases, containing aliases for symbols
    vector<vector<string>> aliases;
public:
    /**
     * @brief Default constructor for Lexer
     */
    Lexer();
    /**
     * @brief Constructor for Lexer
     * @param m mapping from inputs to tokentypes
     * @param a list of supported aliases
     */
    Lexer(const map<string, string> &m, const vector<vector<string>> &a);
    /**
     * @brief Construct a new Lexer object from CFG object
     * @param cfg CFG - cfg object
     */
    explicit Lexer(const std::shared_ptr<CFG>& cfg);
    /**
     * @brief Function to split strings on the characters listed in the delimiter variable
     * @param parseString string to split
     * @return vector with split parts
     */
    vector<string> splitString(const string &parseString);
    /**
     * @brief Function to tokenise a vector of strings
     * @param v vector containing strings
     * @return vector containing tokens for the strings
     */
    vector<ParseToken> tokenise(const vector<string> &v);
    /**
     * @brief Function to tokenise a string, splitting it on ' '
     * @param s string to tokenise
     * @return vector containing tokens for the string
     */
    vector<ParseToken> tokenise(const string &s);
    /**
     * @brief Function to check if a string represents a string
     * @param s the string to check
     * @return true if it represents a string
     */    /**
     * @brief Function to check if a string represents a string
     * @param s the string to check
     * @return true if it represents a string
     */
    bool isString(const string &s);

    /**
     * @brief Function to check if a string represents a number
     * @param s the string to check
     * @return true if it represents a number
     */    /**
     * @brief Function to check if a string represents a number
     * @param s the string to check
     * @return true if it represents a number
     */
    bool isNumber(const string &s);
    /**
     * @brief Function to check if a string represents a name
     * @param s the string to check
     * @return true if it represents a name
     */    /**
     * @brief Function to check if a string represents a name
     * @param s the string to check
     * @return true if it represents a name
     */
    bool isName(const string &s);
    /**
     * @brief Function checking for a delimiter in a string, matching the longest possible delimiter
     * @param s string to check
     * @param offset amount of characters that have been checked already
     * @return length of the found delimiter (0 if none was found)
     */
    unsigned int isDelimiter(const string &s, unsigned int offset);
};


#endif //RATSQL_LEXER_H
