//
// Created by Maarten on 17/12/2021.
//

#include "Parser.h"

#include <iostream>
#include <algorithm>

// Pseudocode
#define LENGTH(vector) vector.size()
#define EMPTY_ORDERED_SET std::vector<ClosureRule>()
#define ADD_TO_SET(set_index, production, origin, current) productionRule[set_index].push_back(ClosureRule(production, origin, current))
#define GRAMMAR_RULES_FOR(nonterminal, grammar) grammar.getRules(nonterminal)
#define IS_TERMINAL(token) token == DIGIT || token == NAME || token == DOT || token == COMMA || token == STRING

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

Production &ClosureRule::getProduction() {
    return production;
}

unsigned int ClosureRule::getOrigin() const {
    return origin;
}

bool ClosureRule::operator==(const ClosureRule &rhs) const {
    if (rhs.closure == closure && rhs.origin == origin &&
        rhs.production.from == production.from && rhs.production.to == production.to) { return true; }
    return false;
}

bool ClosureRule::operator!=(const ClosureRule &rhs) const {
    if (rhs == *this) { return false; }
    return true;
}

// Todo: veranderd van set naar vector, check of er geen dubbels zijn aangemaakt
void Parser::earleyParse(const vector<TokenTypes> &words, Grammar &grammar) {
    // INIT
    // Reserve space in the productionrules
    productionRule = reserveSpaceProductionRules(words.size() + 1);
    // Add sets
    for(int k = 0; k < LENGTH(words); k++) {
        productionRule.emplace_back(EMPTY_ORDERED_SET);
    }

    // EARLEY_PARSE
    // Add basic start rule
    Production startProduction{S_, {grammar.startSymbol}};
    ADD_TO_SET(0, startProduction, 0, 0);
    // Loop over all words
    for (int k = 0; k < LENGTH(words); ++k) {
        cout << "k = " << k << " | Length = " << LENGTH(productionRule[k]) << endl;
        for(int it = 0; it < LENGTH(productionRule[k]); it++) {
            auto state = productionRule[k][it];
//            for (auto &state : productionRule[k]) {
            if (!state.isFinished()) {
                if (!(IS_TERMINAL(state.nextElement()))) {
                    predictor(state, k, grammar);
                } else {
                    scanner(state, k, words);
                }
            } else {
                completer(state, k);
            }
            // TODO: remove duplicates from productionRule[k]
            for(int i = 0; i < productionRule[k].size(); i++) {
                ClosureRule rule = productionRule[k][i];
                for(int j = i+1; j < productionRule[k].size(); j++) {
                    ClosureRule other = productionRule[k][j];
                    if(rule.getProduction().from == other.getProduction().from &&
                    rule.getProduction().to == other.getProduction().to &&
                    rule.getOrigin() == other.getOrigin()) {
                        productionRule[k].erase(productionRule[k].begin() + j);
                    }
                }
            }

        }
    }
    // Remove duplicates inside productionRule
    productionRule.erase(std::unique(std::begin(productionRule), std::end(productionRule)),
                         std::end(productionRule));
}

void Parser::predictor(const ClosureRule &closureRule, unsigned int k, const Grammar &g) {
    for (auto &rule : GRAMMAR_RULES_FOR(closureRule.nextElement(), g)) {
        ADD_TO_SET(k, rule, k, 0);
    }
}

void Parser::scanner(ClosureRule &closureRule, unsigned int k, const vector<TokenTypes> &words) {
    ADD_TO_SET(k+1, closureRule.getProduction(), closureRule.getOrigin(), closureRule.getOrigin() + 1);
}

void Parser::completer(const ClosureRule &closureRule, unsigned int k) {
    for (auto &rule : productionRule[closureRule.getOrigin()]) {
        if (!(IS_TERMINAL(rule.nextElement()))) {
            ADD_TO_SET(k, rule.getProduction(), rule.getOrigin(), rule.getOrigin() + 1);
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
