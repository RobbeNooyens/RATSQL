//
// Created by Maarten on 21/12/2021.
//

#ifndef RATSQL_PARSING_PARSETEMPLATE_H
#define RATSQL_PARSING_PARSETEMPLATE_H

#include <string>
#include <utility>
#include <ostream>

using namespace std;

/**
 * @class ParseToken
 * @brief A class to implement a parse token
 */
class ParseToken {
    /// @brief Type of the token
    string tokenType;

    /// @brief Original content that was turned into this token
    string content;

public:
    /**
     * @brief Constructor for Token
     * @param t Type of the token
     * @param c Content of the token
     */
    ParseToken(string t, string c): tokenType(std::move(t)), content(std::move(c)) {}

    /**
     * @brief Function returning the type of the token
     * @return type of the token
     */
    [[nodiscard]] const string &getToken() const {return tokenType;}

    /**
     * @brief Function returning the content of the token
     * @return content of the token
     */
    [[nodiscard]] const string &getContent() const {return content;}
    /**
     * @brief operator << for a parse template
     * @param os        ostream to cout to
     * @param token     token to cout
     * @return          ostream
     */
    friend ostream &operator<<(ostream &os, const ParseToken &token) {
        os << token.tokenType << "(" << token.content << ")";
        return os;
    }
    /**
     * @brief operator==
     * @param other     object to compare with
     * @return          this == object
     */
    bool operator==(const ParseToken& other) const {
        return tokenType == other.tokenType && content == other.content;
    }
    /**
     * @brief Function to quote content
     */
    void enquote() {
        content = "'" + content + "'";
    }
};


#endif //RATSQL_PARSING_PARSETEMPLATE_H
