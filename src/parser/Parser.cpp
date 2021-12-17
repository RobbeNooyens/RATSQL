//
// Created by Maarten on 17/12/2021.
//

#include "Parser.h"

ClosureRule::ClosureRule(const Production &p, unsigned int o, unsigned int c) : production(p), closure(c), origin(o) {}

bool ClosureRule::isFinished() const {
    return closure == production.to.size();
}

TokenTypes ClosureRule::nextElement() const {
    return production.to[closure];
}

unsigned int ClosureRule::getClosure() const {
    return closure;
}

const Production &ClosureRule::getProduction() const {
    return production;
}

unsigned int ClosureRule::getOrigin() const {
    return origin;
}

// Todo: veranderd van set naar vector, check of er geen dubbels zijn aangemaakt
void Parser::earleyParse(const vector<TokenTypes> &words, Grammar &grammar) {
    // Reserve space in the productionrules
    productionRule = reserveSpaceProductionRules(words.size() + 1);
    // Add basic start rule
    productionRule[0].emplace_back(ClosureRule(Production(S_, {grammar.startSymbol}), 0, 0));
    // Loop over alle words
    for (int i = 0; i < words.size(); ++i) {
        for (auto &currentState : productionRule[i]) {
            if (!currentState.isFinished()) {
                if (currentState.nextElement() == TERMINAL) {
                    predict(currentState, i, grammar);
                } else {
                    scan(currentState, i, words);
                }
            } else {
                complete(currentState, i);
            }
        }
    }
}

void Parser::predict(const ClosureRule &closureRule, unsigned int k, const Grammar &g) {
    for (auto &rule : g.getRules(closureRule.nextElement())) {
        productionRule[k].emplace_back(ClosureRule(rule, k, 0));
    }
}

void Parser::scan(const ClosureRule &closureRule, unsigned int k, const vector<TokenTypes> &words) {
    productionRule[k+1].emplace_back(ClosureRule(closureRule.getProduction(), closureRule.getOrigin(), closureRule.getClosure() + 1));
}

void Parser::complete(const ClosureRule &closureRule, unsigned int k) {
    for (auto &rule : productionRule[closureRule.getOrigin()]) {
        if (rule.nextElement() == closureRule.getProduction().from) {
            productionRule[k].emplace_back(ClosureRule(rule.getProduction(), rule.getOrigin(), rule.getClosure() + 1));
        }
    }
}

ParseTree Parser::makeTree() const {
    ParseTree tree;
    return tree;
}

std::vector<std::vector<ClosureRule>> Parser::reserveSpaceProductionRules(unsigned int size) {
    std::vector<std::vector<ClosureRule>> v;
    v.reserve(size);
    for (int i = 0; i < size; ++i) {
        v.emplace_back(std::vector<ClosureRule>{});
    }
    return v;
}

