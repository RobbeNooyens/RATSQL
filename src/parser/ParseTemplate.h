//
// Created by Maarten on 21/12/2021.
//

#ifndef RATSQL_PARSING_PARSETEMPLATE_H
#define RATSQL_PARSING_PARSETEMPLATE_H

#include <string>
#include <utility>
#include <ostream>

using namespace std;

class ParseToken {
    /// Type of the token
    string tokenType;

    /// Original content that was turned into this token
    string content;

public:
    /**
     * Constructor for Token
     * @param t Type of the token
     * @param c Content of the token
     */
    ParseToken(string t, string c): tokenType(std::move(t)), content(std::move(c)) {}

    /**
     * Function returning the type of the token
     * @return type of the token
     */
    const string &getToken() const {return tokenType;}

    /**
     * Function returning the content of the token
     * @return content of the token
     */
    const string &getContent() const {return content;}

    friend ostream &operator<<(ostream &os, const ParseToken &token) {
        os << token.tokenType << "(" << token.content << ")";
        return os;
    }
};


#endif //RATSQL_PARSING_PARSETEMPLATE_H
