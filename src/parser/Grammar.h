//
// Created by Maarten on 06/12/2021.
//

#ifndef RATSQL_GRAMMAR_H
#define RATSQL_GRAMMAR_H

#include "Token.h"
#include <map>
#include <vector>

static std::vector<std::vector<std::string>> names = {{"pi", "π"}, {"sigma", "σ"}, {"rho", "ρ"}, {"←"}, {"→"}, {"and", "∧"},
                                               {"or", "∨"}, {"¬"}, {"="}, {"!=", "≠"}, {"≥", ">="}, {"≤", "<="},
                                               {"intersect", "∩"}, {"union", "∪"}, {"÷", "/"}, {"-"}, {"⨯", "x"},
                                               {"⨝"}, {"--"}, {"/*"}, {"*/"}, {"("}, {")"}, {"."}};
static std::vector<TokenTypes> tokens = {PI, SIGMA, RHO, LEFTARROW, RIGHTARROW, AND, OR, NOT, EQ, NEQ, GEQ, LEQ, INTERSECT, UNION,
                                  DIV, SUB, SCALAR, JOIN, COMMENT, MULTI_COMMENT_START, MULTI_COMMENT_STOP,
                                  CURLY_BRACKET_LEFT, CURLY_BRACKET_RIGHT, ROUNDED_BRACKET_LEFT, ROUNDED_BRACKET_RIGHT, DOT};

static std::map<std::string, TokenTypes> generateTokenMap() {
    std::map<std::string, TokenTypes> map;
    for (int i = 0; i < names.size(); ++i) {
        for (auto &name : names[i]) {
            map.emplace(name, tokens[i]);
        }
    }
    return map;
}

#endif //RATSQL_GRAMMAR_H
