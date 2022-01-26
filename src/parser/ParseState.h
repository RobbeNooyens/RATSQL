//
// Created by robnoo on 3/01/22.
//

#ifndef RATSQL_PARSING_PARSESTATE_H
#define RATSQL_PARSING_PARSESTATE_H


#include <string>
#include <vector>
#include <memory>
#include "../datastructures/CFG.h"

class TreeNode;

class ParseState {
public:
    // Constructor
    ParseState(ProductionRule production, unsigned int dot, unsigned int origin);

    // Getters
    const ProductionRule& getProduction();
    unsigned int getDot() const;
    unsigned int getOrigin() const;
    const std::string& nextElement();
    std::vector<std::pair<ParseState*, ParseState*>>& getDerivedStates();
    bool isFinished();
    std::string toString();

    // Actions
    void addDerivedState(std::pair<ParseState*, ParseState*> state);
    void evaluate(TreeNode *tree);

    // Comparators
    bool operator==(ParseState& rhs);
    bool operator!=(ParseState& rhs);

private:
    ProductionRule production;
    unsigned int dot = 0;
    unsigned int origin = 0;
    std::vector<std::pair<ParseState*, ParseState*>> derivedStates;

    TreeNode *createNode(const std::string &s) const;
};


#endif //RATSQL_PARSING_PARSESTATE_H
