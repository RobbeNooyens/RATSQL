//
// Created by Maarten on 17/12/2021.
//

#include "Parser.h"

#include <iostream>
#include <utility>
#include <sstream>

// Pseudocode
#define LENGTH(vector) vector.size()
#define EMPTY_ORDERED_SET std::vector<ParseState>()
#define ADD_TO_SET(set_index, production, dot, origin) S[set_index].push_back(ParseState(production, dot, origin))
#define GRAMMAR_RULES_FOR(nonterminal) cfg->getRules(nonterminal)
//#define IS_TERMINAL(token) cfg->isTerminal(token)
#define IS_VARIABLE(token) cfg->isVariable(token)

using namespace std;

// Todo: veranderd van set naar vector, check of er geen dubbels zijn aangemaakt
void Parser::earleyParse(const std::vector<TokenTemplate> &words) {
    // INIT
    // Reserve space in the productionrules
    S.reserve(LENGTH(words) + 1);
    for(int k = 0; k < LENGTH(words) + 1; k++) {
        S.emplace_back(EMPTY_ORDERED_SET);
    }

    // EARLEY_PARSE
    // Add basic start rule
    Production startProduction{"S_", {cfg->getStartSymbol()}};
    ADD_TO_SET(0, startProduction, 0, 0);
    // Loop over all words
    for (int k = 0; k < LENGTH(words) + 1; ++k) {
//        cout << "=========" << endl << "k = " << k << " | Length = " << LENGTH(S[k]) << endl << "=========" << endl;
        for(int it = 0; it < LENGTH(S[k]); it++) {
            auto state = S[k][it];
            if (!state.isFinished()) {
                if (IS_VARIABLE(state.nextElement())) {
                    predictor(state, k);
                } else {
                    scanner(state, k, words);
                }
            } else {
                completer(state, k);
            }
            // remove duplicates
            removeDuplicates(k);
//            for(int i = 0; i < S[k].size(); i++) {
//                ParseState rule = S[k][i];
//                for(int j = i+1; j < S[k].size(); j++) {
//                    if(rule == S[k][j]) {
//                        S[k].erase(S[k].begin() + j);
//                    }
//                }
//            }
        }
    }
    for(int k = 0; k < S.size(); k++) {
        cout << "=====[ k = " << k << " ]=====" << endl;
        for(auto& state: S[k]) {
            cout << state.toString() << endl;
        }
    }
}

void Parser::predictor(ParseState &state, unsigned int k) {
    for (auto &rule : GRAMMAR_RULES_FOR(state.nextElement())) {
        ADD_TO_SET(k, rule, 0, k);
    }
}

void Parser::scanner(ParseState &state, unsigned int k, const vector<TokenTemplate> &words) {
    if(state.nextElement() == words[k].getType())
        ADD_TO_SET(k+1, state.getProduction(), state.getDot() + 1, state.getOrigin());
}

void Parser::completer(ParseState &state, unsigned int k) {
    for (auto &rule : S[state.getOrigin()]) {
        if (rule.nextElement() == state.getProduction().first) {
            ADD_TO_SET(k, rule.getProduction(), rule.getDot() + 1, rule.getOrigin());
        }
    }
}

Parser::Parser(std::unique_ptr<CFG> g) : cfg(move(g)) {}

void Parser::removeDuplicates(int k) {
    // remove duplicates
    for(int i = 0; i < S[k].size(); i++) {
        ParseState rule = S[k][i];
        for(int j = i+1; j < S[k].size(); j++) {
            if (rule == S[k][j]) {
                S[k].erase(S[k].begin() + j);
            }
        }
    }
}


// ParseState

ParseState::ParseState(Production production, int dot, int origin): production(std::move(production)), dot(dot), origin(origin) {};

const Production &ParseState::getProduction() {
    return production;
}

int ParseState::getDot() const {
    return dot;
}

int ParseState::getOrigin() const {
    return origin;
}

const std::string &ParseState::nextElement() {
    return production.second[dot];
}

bool ParseState::isFinished() {
    return dot >= production.second.size();
}

//bool ParseState::operator==(const ParseState &rhs) {
//    if(dot != rhs.dot || origin != rhs.origin)
//        return false;
//    if(production.head != rhs.production.head || production.body != rhs.production.body)
//        return false;
//    return true;
//}
//
//bool ParseState::operator!=(const ParseState &rhs) {
//    return !(*this == rhs);
//}

bool ParseState::operator==(ParseState &rhs) const {
    if(dot != rhs.dot || origin != rhs.origin)
        return false;
    if(production.first != rhs.production.first || production.second != rhs.production.second)
        return false;
    return true;
}

bool ParseState::operator!=(ParseState &rhs) const {
    return !(*this == rhs);
}

std::string ParseState::toString() {
    std::stringstream output;
    output << production.first << " -> ";
    for(int i = 0; i < production.second.size(); i++) {
        if(i == dot) {
            output << "• ";
        }
        output << production.second[i] << " ";
    }
    if(dot == production.second.size())
        output << "• ";
    output << " [" << origin << "]";
    return output.str();
}
