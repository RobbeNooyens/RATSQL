//
// Created by robnoo on 3/01/22.
//

#include <sstream>
#include "ParseState.h"
#include "Tree.h"
#include "../datastructures/CFG.h"

ParseState::ParseState(ProductionRule production, unsigned int dot, unsigned int origin): production(std::move(production)), dot(dot), origin(origin) {};

const ProductionRule &ParseState::getProduction() {
    return production;
}

unsigned int ParseState::getDot() const {
    return dot;
}

unsigned int ParseState::getOrigin() const {
    return origin;
}

const std::string &ParseState::nextElement() {
    return production.second[dot];
}

bool ParseState::isFinished() {
    return dot >= production.second.size();
}

std::vector<std::pair<ParseState*, ParseState*>> &ParseState::getDerivedStates() {
    return derivedStates;
}

void ParseState::addDerivedState(std::pair<ParseState*, ParseState*> state) {
    derivedStates.push_back(state);
}

void ParseState::evaluate(Tree *tree) {
    // Predict
    if(dot == 0) {
        return;
    }
    auto statePair = derivedStates.front();
    if(statePair.second) {
        // Complete
        if(dot == production.second.size()) {
            for(auto& s: production.second) {
                tree->addChild(new Tree(s));
            }
        }
        statePair.first->evaluate(tree->getChild(dot - 1));
        statePair.second->evaluate(tree);
    } else {
        // Scan
        if(tree->getChildren().empty())
            tree->addChild(new Tree(production.second[dot-1])); // Add single terminals
        else
            statePair.first->evaluate(tree);
    }
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

bool ParseState::operator==(ParseState &rhs) {
    if(dot != rhs.dot || origin != rhs.origin)
        return false;
    if(production.first != rhs.production.first || production.second != rhs.production.second)
        return false;
    return true;
}

bool ParseState::operator!=(ParseState &rhs) {
    return !(*this == rhs);
}
