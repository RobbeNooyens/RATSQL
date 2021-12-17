//
// Created by Maarten on 28/11/2021.
//

#ifndef RATSQL_LEXER_H
#define RATSQL_LEXER_H

#include "Grammar.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Lexer {
private:
    const char delimiter = ' ';

    map<wstring, TokenTypes> tokenMap;

public:
    /**
     * Constructor for Relax Parser
     * @param parseString string to parse
     */
    Lexer();

//    vector<Token> tokenise(const string &s);

    /**
     * Function to split strings on the characters listed in the delimiter variable
     * @param parseString string to split
     * @return vector with split parts
     */
    vector<wstring> splitString(const wstring &parseString);

    /**
     * Function to tokenise a vector of strings
     * @param v vector containing strings
     * @return vector containing tokens for the strings
     */
    vector<Token> tokenise(const vector<wstring> &v);

    /**
     * Function to tokenise a string, splitting it on ' '
     * @param s string to tokenise
     * @return vector containing tokens for the string
     */
    vector<Token> tokenise(const wstring &s);

    /**
     * Function to check if a string represents a string
     * @param s the string to check
     * @return true if it represents a string
     */    /**
     * Function to check if a string represents a string
     * @param s the string to check
     * @return true if it represents a string
     */
    bool isString(const wstring &s);

    /**
     * Function to check if a string represents a number
     * @param s the string to check
     * @return true if it represents a number
     */    /**
     * Function to check if a string represents a number
     * @param s the string to check
     * @return true if it represents a number
     */
    bool isNumber(const wstring &s);

    /**
     * Function to check if a string represents a name
     * @param s the string to check
     * @return true if it represents a name
     */    /**
     * Function to check if a string represents a name
     * @param s the string to check
     * @return true if it represents a name
     */
    bool isName(const wstring &s);

    unsigned int isDelimiter(const wstring &s, unsigned int offset);
};


#endif //RATSQL_LEXER_H
