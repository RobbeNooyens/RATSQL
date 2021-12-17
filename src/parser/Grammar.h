//
// Created by Maarten on 06/12/2021.
//

#ifndef RATSQL_GRAMMAR_H
#define RATSQL_GRAMMAR_H

#include "Token.h"
#include <map>
#include <vector>


class Production {
public:
    TokenTypes from;
    std::vector<TokenTypes> to;
};

using ProductionRules = std::vector<Production>;

static std::vector<std::vector<std::string>> names = {{"pi",        "π"},
                                                      {"sigma",     "σ"},
                                                      {"rho",       "ρ"},
                                                      {"←"},
                                                      {"→"},
                                                      {"and",       "∧"},
                                                      {"or",        "∨"},
                                                      {"¬"},
                                                      {"="},
                                                      {"!=",        "≠"},
                                                      {"≥",         ">="},
                                                      {"≤",         "<="},
                                                      {"intersect", "∩"},
                                                      {"union",     "∪"},
                                                      {"÷",         "/"},
                                                      {"-"},
                                                      {"⨯",         "x"},
                                                      {"⨝",         "join"},
                                                      {"--"},
                                                      {"/*"},
                                                      {"*/"},
                                                      {"("},
                                                      {")"},
                                                      {"."}};
static std::vector<TokenTypes> tokens = {PI, SIGMA, RHO, LEFTARROW, RIGHTARROW, AND, OR, NOT, EQ, NEQ, GEQ, LEQ,
                                         INTERSECT, UNION,
                                         DIV, SUB, SCALAR, JOIN, COMMENT, MULTI_COMMENT_START, MULTI_COMMENT_STOP,
                                         CURLY_BRACKET_LEFT, CURLY_BRACKET_RIGHT, ROUNDED_BRACKET_LEFT,
                                         ROUNDED_BRACKET_RIGHT, DOT};

static ProductionRules productions {
        {S, {EXPRESSION}},
        {S, {NAME, EQ, EXPRESSION}},
        {EXPRESSION, {TABLE}},
        {EXPRESSION, {MODIFICATION, EXPRESSION}},
        {MODIFICATION, {PROJECTION}},
        {MODIFICATION, {SELECTION}},
        {MODIFICATION, {RENAME}},
        {MODIFICATION, {JOIN}},

        {JOIN, {PROJECTION}},
        {JOIN, {SELECTION}},
        {JOIN, {RENAME}},
        {JOIN, {JOIN}},
        {SELECTION, {SIGMA}},
        {SELECTION, {EQUATION}},
        {PROJECTION, {PI}},
        {PROJECTION, {COLUMN_NAME}},
        {RENAME, {RHO}},
        {RENAME, {RENAME_PREMISE}},

        {RENAME_PREMISE, {NAME, RENAME_SYMBOL, NAME}},
        {RENAME_SYMBOL, {LEFTARROW}},
        {RENAME_SYMBOL, {RIGHTARROW}},

//        {OPERATOR1, {{EQ}, {NEQ}, {GEQ}, {LEQ}}},
//        {OPERATOR2, {{AND}, }},
//
//        {TABLE, {{ROUNDED_BRACKET_LEFT, TABLE, OPERATOR3, TABLE, ROUNDED_BRACKET_RIGHT},
//                   {TABLE, OPERATOR3, TABLE}, {TABLE_NAME}, {ROUNDED_BRACKET_LEFT, TABLE_NAME, ROUNDED_BRACKET_RIGHT}}},
//
//        {OPERATOR3, {{INTERSECT}, {UNION}, {DIV}, {SUB}, {JOIN}, {SCALAR}}},
//
//        {EQUATION, {{NOT, ROUNDED_BRACKET_LEFT}, {EQUATION}, {ROUNDED_BRACKET_RIGHT}, {VAR, OPERATOR1, VAR}, {EQUATION, OPERATOR2, EQUATION}}},
//
//        {VAR, {{COLUMN_NAME}, {NUMBER}, {STRING}}},
//        {NUMBER, {{DIGIT}, {DIGIT, DOT, DIGIT}}},


};

struct Grammar {
    std::string startSymbol = "S";

    ProductionRules productionRules = productions;
};

static std::map<std::string, TokenTypes> generateTokenMap() {
    std::map<std::string, TokenTypes> map;
    for (int i = 0; i < names.size(); ++i) {
        for (auto &name: names[i]) {
            map.emplace(name, tokens[i]);
        }
    }
    return map;
}

#endif //RATSQL_GRAMMAR_H
