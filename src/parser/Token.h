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
    LT,
    GT,
    INTERSECT,
    UNION,
    DIV,
    SUB,
    SCALAR,
    JOIN,
    JOIN_OP,
    COMMENT,
    MULTI_COMMENT_START,
    MULTI_COMMENT_STOP,
    CURLY_BRACKET_LEFT,
    CURLY_BRACKET_RIGHT,
    ROUNDED_BRACKET_LEFT,
    ROUNDED_BRACKET_RIGHT,
    DOT,
    COMMA,
    NAME,
    NUMBER,
    STRING,
    TERMINAL,
    PROJECTION_PREMISE,
    QUOTE
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
    {LT, "LT"},
    {GT, "GT"},
};

class Token {
    /// Type of the token
    TokenTypes tokenType;

    /// Original content that was turned into this token
    wstring content;

public:
    /**
     * Constructor for Token
     * @param t Type of the token
     * @param c Content of the token
     */
    Token(TokenTypes t, const wstring &c): tokenType(t), content(c) {}

    /**
     * Function returning the type of the token
     * @return type of the token
     */
    TokenTypes getType() const {return tokenType;}

    /**
     * Function returning the content of the token
     * @return content of the token
     */
    const wstring& getContent() const {return content;}
};

#endif //RATSQL_TOKEN_H
