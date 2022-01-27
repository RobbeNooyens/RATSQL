//
// Created by robnoo on 3/01/22.
//

#include <sstream>
#include "ParseState.h"
#include "TreeNode.h"

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

void ParseState::evaluate(TreeNode *tree) {
    // Predict
    if(dot == 0) {
        return;
    }
    auto statePair = derivedStates.front();
    if(dot == production.second.size()) {
        for(auto& s: production.second) {
            auto ptr = createNode(s);
            tree->addChild(ptr);
        }
    }
    if(statePair.second) {
        // Complete
        statePair.first->evaluate(tree->getChild(dot - 1));
        statePair.second->evaluate(tree);
    } else {
        // Scan
        statePair.first->evaluate(tree);
    }
}

TreeNode* ParseState::createNode(const std::string &s) const {
    if (s == "DOT" || s == "DIGIT" || s == "NAME" || s == "COMMA" || s == "EQ" || s == "ROUNDED_BRACKET_LEFT" ||
        s == "ROUNDED_BRACKET_RIGHT" || s == "LT" || s == "GT" || s == "LEQ" || s == "GEQ" || s == "NEQ" || s == "EOL") {
        return new BasicNode(s);
    } else if (s == "S") {
        return new RootNode(s);
    } else if (s == "SELECTION") {
        return new SelectionNode(s);
    } else if (s == "EXPRESSION") {
        return new ExpressionNode(s);
    } else if (s == "MODIFICATION") {
        return new ModificationNode(s);
    } else if (s == "SELECTION") {
        return new SelectionNode(s);
    } else if (s == "PROJECTION") {
        return new ProjectionNode(s);
    } else if (s == "RENAME") {
        return new RenameNode(s);
    } else if (s == "TABLE") {
        return new TableNode(s);
    } else if (s == "AND" || s == "OR") {
        return new ValueNode(s);
    } else if (s == "NEQ") {
        return new ValueNode("!=");
    } else if (s == "QUOTE") {
        return new ValueNode("'");
    } else if (s == "RENAME_PREMISE") {
        return new RenamePremiseNode(s);
    } else if (s == "JOIN_OP") {
        return new JoinNode(s);
    } else if (s == "SET_OP") {
        return new SetOperatorNode(s);
    } else if (s == "UNION" || s == "INTERSECT") {
        return new ValueNode(s);
    }


    else {
        return new TreeNode(s);
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
