//
// Created by Maarten on 17/12/2021.
//

#include "EarleyParser.h"
#include "TreeNode.h"
#include "ParseState.h"

#include "../utilities/Utils.h"

#include <utility>
#include <sstream>

// Pseudocode
#define LENGTH(vector) vector.size()
#define EMPTY_ORDERED_SET std::vector<ParseState*>()
#define ADD_TO_SET(set_index, production, dot, origin) ParseState* stateToAdd = new ParseState(production, dot, origin); S[set_index].push_back(stateToAdd)
#define GRAMMAR_RULES_FOR(nonterminal) cfg->getRules(nonterminal)
//#define IS_TERMINAL(token) cfg->isTerminal(token)
#define IS_VARIABLE(token) !cfg->isTerminal(token)
#define CONSTRUCT_TREE(stateFrom) stateToAdd->addDerivedState(stateFrom)

using namespace std;

TreeNode * EarleyParser::earleyParse(const vector<ParseToken> &tokens) {
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
//    ParseState* s = new ParseState(startProduction, 0, 0);
//    Utils::emplace_back_unique(S[0], s);
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
            // remove duplicates --> Changed by using emplace_unique
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
    ParseState* initReplacement = nullptr;
    for(auto& state: S[S.size()-1]) {
        if(state->getProduction().first == "S_") {
            initReplacement = state;
            break;
        }
    }
    if(initReplacement) {
        TreeNode* root = new TreeNode("S_");
        initReplacement->evaluate(root);
        int index = 0;
        root->assignTokens(tokens, index);
        std::string output = "output/out.dot";
        root->exportDot(output);
        if(index != tokens.size()) {
            throw std::runtime_error("Index should be at end of vector");
        }
        return root;
    }
    return nullptr;
}

void EarleyParser::predictor(ParseState* state, unsigned int k) {
    for (auto &rule : GRAMMAR_RULES_FOR(state->nextElement())) {
        ADD_TO_SET(k, rule, 0, k);
//        ParseState* s = new ParseState(rule, 0, k);
//        Utils::emplace_back_unique(S[k], s);
    }
}

void EarleyParser::scanner(ParseState* state, unsigned int k, const vector<ParseToken> &tokens) {
    if(state->nextElement() == tokens[k].getToken()) {
        ADD_TO_SET(k+1, state->getProduction(), state->getDot() + 1, state->getOrigin());
//        ParseState* s = new ParseState(state->getProduction(), state->getDot() + 1, state->getOrigin());
//        Utils::emplace_back_unique(S[k + 1], s);
        std::pair<ParseState*, ParseState*> pair = {state, nullptr};
        CONSTRUCT_TREE(pair);
//        s->addDerivedState(pair);
    }
}

void EarleyParser::completer(ParseState* state, unsigned int k) {
    for (auto &rule : S[state->getOrigin()]) {
        if (rule->nextElement() == state->getProduction().first) {
            ADD_TO_SET(k, rule->getProduction(), rule->getDot() + 1, rule->getOrigin());
//            ParseState* s = new ParseState(rule->getProduction(), rule->getDot() + 1, rule->getOrigin());
//            Utils::emplace_back_unique(S[k], s);
            std::pair<ParseState*, ParseState*> pair = {state, rule};
            CONSTRUCT_TREE(pair);
//            s->addDerivedState(pair);
        }
    }
}

EarleyParser::EarleyParser(std::string& grammar) {
    cfg = std::make_shared<CFG>(grammar);
}

EarleyParser::~EarleyParser() {
    for(int i = 0; i < S.size(); i++) {
        for(int j = 0; j < S[i].size(); j++) {
            delete S[i][j];
            S[i][j] = nullptr;
        }
    }
}

EarleyParser::EarleyParser(const shared_ptr<CFG> &cfg): cfg(cfg) {}
