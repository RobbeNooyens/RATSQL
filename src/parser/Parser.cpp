//
// Created by Maarten on 17/12/2021.
//

#include "Parser.h"

ClosureRule::ClosureRule(const Production &p, unsigned int c): production(p), closure(c) {}

void Parser::earlyParse(vector<string> &words, const Grammar &grammar) {
    std::string left = "";
    std::vector<std::string> temp = {"S"};
    productionRule.push_back(Production(left, {{grammar.startSymbol}}));
}
