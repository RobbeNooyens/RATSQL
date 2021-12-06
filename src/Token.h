//
// Created by Cédric Leclercq on 25/11/2021.
//

#ifndef RATSQL_TOKEN_H
#define RATSQL_TOKEN_H

enum Tokens {
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
    ROUNDED_BRACKET_RIGHT
};

#endif //RATSQL_TOKEN_H
