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

    unsigned int getRightSize() const {return to.size();}

    Production(TokenTypes left, std::vector<TokenTypes> right): from(left), to(move(right)) {}
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
                                                      {"<"},
                                                      {">"},
                                                      {"intersect", "∩"},
                                                      {"union",     "∪"},
                                                      {"÷",         "/"},
                                                      {"-"},
                                                      {"⨯",         "x"},
                                                      {"⨝",         "join"},
                                                      {"--"},
                                                      {"/*"},
                                                      {"*/"},
                                                      {"{"},
                                                      {"}"},
                                                      {"("},
                                                      {")"},
                                                      {"."}};

static std::vector<TokenTypes> tokens = {PI, SIGMA, RHO, LEFTARROW, RIGHTARROW, AND, OR, NOT, EQ, NEQ, GEQ, LEQ, LT, GT,
                                         INTERSECT, UNION,
                                         DIV, SUB, SCALAR, JOIN, COMMENT, MULTI_COMMENT_START, MULTI_COMMENT_STOP,
                                         CURLY_BRACKET_LEFT, CURLY_BRACKET_RIGHT, ROUNDED_BRACKET_LEFT,
                                         ROUNDED_BRACKET_RIGHT, DOT, TERMINAL};

static ProductionRules productions {
        Production(S, {EXPRESSION}),
        Production(S, {NAME, EQ, EXPRESSION}),
        Production(EXPRESSION, {TABLE}),
        Production(EXPRESSION, {MODIFICATION, EXPRESSION}),
        Production(MODIFICATION, {PROJECTION}),
        Production(MODIFICATION, {SELECTION}),
        Production(MODIFICATION, {RENAME}),
        Production(MODIFICATION, {JOIN}),

        Production(JOIN, {PROJECTION}),
        Production(JOIN, {SELECTION}),
        Production(JOIN, {RENAME}),
        Production(JOIN, {JOIN}),
        Production(SELECTION, {SIGMA}),
        Production(SELECTION, {EQUATION}),
        Production(PROJECTION, {PI}),
        Production(PROJECTION, {COLUMN_NAME}),
        Production(RENAME, {RHO}),
        Production(RENAME, {RENAME_PREMISE}),

        Production(RENAME_PREMISE, {NAME, RENAME_SYMBOL, NAME}),
        Production(RENAME_SYMBOL, {LEFTARROW}),
        Production(RENAME_SYMBOL, {RIGHTARROW}),

        Production(OPERATOR1, {EQ}),
        Production(OPERATOR1, {NEQ}),
        Production(OPERATOR1, {GEQ}),
        Production(OPERATOR1, {LEQ}),
        Production(OPERATOR2, {AND}),

        Production(TABLE, {ROUNDED_BRACKET_LEFT, TABLE, OPERATOR3, TABLE, ROUNDED_BRACKET_RIGHT}),
        Production(TABLE, {TABLE, OPERATOR3, TABLE}),
        Production(TABLE, {TABLE_NAME}),
        Production(TABLE, {ROUNDED_BRACKET_LEFT, TABLE_NAME, ROUNDED_BRACKET_RIGHT}),

        Production(OPERATOR3, {INTERSECT}),
        Production(OPERATOR3, {UNION}),
        Production(OPERATOR3, {DIV}),
        Production(OPERATOR3, {SUB}),
        Production(OPERATOR3, {JOIN}),
        Production(OPERATOR3, {SCALAR}),

        Production(EQUATION, {NOT, ROUNDED_BRACKET_LEFT}),
        Production(EQUATION, {EQUATION}),
        Production(EQUATION, {ROUNDED_BRACKET_RIGHT}),
        Production(EQUATION, {VAR, OPERATOR1, VAR}),
        Production(EQUATION, {EQUATION, OPERATOR2, EQUATION}),

        Production(VAR, {COLUMN_NAME}),
        Production(VAR, {NUMBER}),
        Production(VAR, {STRING}),
        Production(NUMBER, {DIGIT}),
        Production(NUMBER, {DIGIT, DOT, DIGIT}),

};

struct Grammar {
    TokenTypes startSymbol = S;

    ProductionRules productionRules = productions;

    ProductionRules getRules(TokenTypes t) const {
        ProductionRules result;
        for (auto &p : productionRules) {
            if (p.from == t) {
                result.emplace_back(p);
            }
        }
        return result;
    }
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
