//
// Created by Maarten on 17/12/2021.
//

#include "Parser.h"
#include "Tree.h"
#include "ParseState.h"

#include <iostream>
#include <utility>
#include <sstream>

// Pseudocode
#define LENGTH(vector) vector.size()
#define EMPTY_ORDERED_SET std::vector<ParseState*>()
#define ADD_TO_SET(set_index, production, dot, origin) ParseState* stateToAdd = new ParseState(production, dot, origin); S[set_index].push_back(stateToAdd)
#define GRAMMAR_RULES_FOR(nonterminal) cfg->getRules(nonterminal)
//#define IS_TERMINAL(token) cfg->isTerminal(token)
#define IS_VARIABLE(token) cfg->isVariable(token)
#define CONSTRUCT_TREE(stateFrom) stateToAdd->addDerivedState(stateFrom)

using namespace std;

// Todo: veranderd van set naar vector, check of er geen dubbels zijn aangemaakt
void Parser::earleyParse(const vector<ParseToken> &tokens) {
    // INIT
    // Reserve space in the productionrules
    S.reserve(LENGTH(tokens) + 1);
    for(int k = 0; k < LENGTH(tokens) + 1; k++) {
        S.emplace_back(EMPTY_ORDERED_SET);
    }

    // EARLEY_PARSE
    // Add basic start rule
    ProductionRule startProduction{"S_", {cfg->getStartSymbol()}};
    ADD_TO_SET(0, startProduction, 0, 0);
    // Loop over all words
    for (int k = 0; k < LENGTH(tokens) + 1; ++k) {
        for(int it = 0; it < LENGTH(S[k]); it++) {
            auto state = S[k][it];
            if (!state->isFinished()) {
                if (IS_VARIABLE(state->nextElement())) {
                    predictor(state, k);
                } else {
                    scanner(state, k, tokens);
                }
            } else {
                completer(state, k);
            }
            // remove duplicates
            for(int i = 0; i < S[k].size(); i++) {
                ParseState* rule = S[k][i];
                for(int j = i+1; j < S[k].size(); j++) {
                    ParseState* other = S[k][j];
                    if(*rule == *other) {
                        for(auto& derivedState: other->getDerivedStates()) {
                            rule->addDerivedState(derivedState);
                        }
                        delete other;
                        S[k].erase(S[k].begin() + j);
                    }
                }
            }

        }
    }
    for(int k = 0; k < S.size(); k++) {
        cout << "=====[ k = " << k << " ]=====" << endl;
        for(auto& state: S[k]) {
            cout << state->toString() << endl;
        }
    }
    ParseState* initReplacement = nullptr;
    for(auto& state: S[S.size()-1]) {
        if(state->getProduction().first == "S_") {
            initReplacement = state;
            break;
        }
    }
    if(initReplacement) {
        Tree* root = new Tree("S_");
        initReplacement->evaluate(root);
        int index = 0;
        root->assignTokens(tokens, index);
        std::string output = "../output/out.dot";
        root->exportDot(output);
        if(index != tokens.size()) {
            throw std::runtime_error("Index should be at end of vector");
        }
    }



}

void Parser::predictor(ParseState* state, unsigned int k) {
    for (auto &rule : GRAMMAR_RULES_FOR(state->nextElement())) {
        ADD_TO_SET(k, rule, 0, k);
    }
}

void Parser::scanner(ParseState* state, unsigned int k, const vector<ParseToken> &tokens) {
    if(state->nextElement() == tokens[k].getToken()) {
        ADD_TO_SET(k+1, state->getProduction(), state->getDot() + 1, state->getOrigin());
        std::pair<ParseState*, ParseState*> pair = {state, nullptr};
        CONSTRUCT_TREE(pair);
    }
}

void Parser::completer(ParseState* state, unsigned int k) {
    for (auto &rule : S[state->getOrigin()]) {
        if (rule->nextElement() == state->getProduction().first) {
            ADD_TO_SET(k, rule->getProduction(), rule->getDot() + 1, rule->getOrigin());
            std::pair<ParseState*, ParseState*> pair = {state, rule};
            CONSTRUCT_TREE(pair);
        }
    }
}

Parser::Parser(std::string& grammar) {
    cfg = std::make_shared<CFG>(grammar);
}

Parser::~Parser() {
    for(int i = 0; i < S.size(); i++) {
        for(int j = 0; j < S[i].size(); j++) {
            delete S[i][j];
            S[i][j] = nullptr;
        }
    }
}