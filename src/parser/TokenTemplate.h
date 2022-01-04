//
// Created by Maarten on 21/12/2021.
//

#ifndef RATSQL_PARSING_TOKENTEMPLATE_H
#define RATSQL_PARSING_TOKENTEMPLATE_H

#include <string>

using namespace std;

class TokenTemplate {
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
    TokenTemplate(const string &t, const string &c): tokenType(t), content(c) {}

    /**
     * Function returning the type of the token
     * @return type of the token
     */
    const string &getType() const {return tokenType;}

    /**
     * Function returning the content of the token
     * @return content of the token
     */
    const string & getContent() const {return content;}
};


#endif //RATSQL_PARSING_TOKENTEMPLATE_H
