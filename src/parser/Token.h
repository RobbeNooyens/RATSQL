//
// Created by Cédric Leclercq on 25/11/2021.
//

#ifndef RATSQL_TOKEN_H
#define RATSQL_TOKEN_H

#include <string>
#include <map>


enum TokenTypes {
    // GRAMMATICA
    S_, S, EXPRESSION, TABLE, MODIFICATION, PROJECTION, SELECTION, RENAME, EQUATION, RENAME_PREMISE, COLUMN_NAME, RENAME_SYMBOL, OPERATOR1, OPERATOR2, OPERATOR3, TABLE_NAME, VAR, DIGIT,



    // PARSING

    PI,
    SIGMA,
    RHO,
    LEFTARROW,
    RIGHTARROW,
    AND,
    OR,
    NOT,
    EQ,
    NEQ,
    GEQ,
    LEQ,
    INTERSECT,
    UNION,
    DIV,
    SUB,
    SCALAR,
    JOIN,
    COMMENT,
    MULTI_COMMENT_START,
    MULTI_COMMENT_STOP,
    CURLY_BRACKET_LEFT,
    CURLY_BRACKET_RIGHT,
    ROUNDED_BRACKET_LEFT,
    ROUNDED_BRACKET_RIGHT,
    DOT,
    NAME,
    NUMBER,
    STRING,
    TERMINAL
};

using namespace std;

static map<TokenTypes, string> toString{
    {PI, "PI"},
    {SIGMA, "SIGMA"},
    {RHO, "RHO"},
    {LEFTARROW, "LEFTARROW"},
    {RIGHTARROW, "LEFTARROW"},
    {ROUNDED_BRACKET_LEFT, "ROUNDED_BRACKET_LEFT"},
    {ROUNDED_BRACKET_RIGHT, "ROUNDED_BRACKET_RIGHTT"},
    {STRING, "STRING"},
    {NAME, "NAME"},
    {STRING, "STRING"},
    {DOT, "DOT"},
    {JOIN, "JOIN"},
    {LEQ, "LT"},
    {GEQ, "GT"},
};

class Token {
    /// Type of the token
    TokenTypes tokenType;

    /// Original content that was turned into this token
    string content;

public:
    /**
     * Constructor for Token
     * @param t Type of the token
     * @param c Content of the token
     */
    Token(TokenTypes t, const string &c): tokenType(t), content(c) {}

    TokenTypes getType() {return tokenType;}
};

#endif //RATSQL_TOKEN_H
