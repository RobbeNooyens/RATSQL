//
// Created by Maarten on 17/12/2021.
//

#ifndef RATSQL_SHUNTING_YARD_PARSER_H
#define RATSQL_SHUNTING_YARD_PARSER_H

#include <string>
#include <vector>
#include <set>

#include "Grammar.h"
#include "../datastructures/ParseTree.h"

class ClosureRule {
    /// Production on which the closure is based
    Production production;

    /// Position of the closure
    unsigned int closure;

    /// Origin of the closure rule
    unsigned int origin;

public:
    /**
     * Constructor for closure rule
     * @param p production used to make the closure rule
     * @param o origin of the closure rule
     * @param c index of the closure (0 by default)
     */
    ClosureRule(const Production &p, unsigned int o, unsigned int c = 0);

    /**
     * Getter for the closure
     * @return the index where the closure is
     */
    unsigned int getClosure() const;

    /**
     * Function to check whether a closure has reached the end of a right side
     * @return true if yes
     */
    bool isFinished() const;

    /**
     * Function that returns the next element in the productionrule
     * @return the next token
     */
    TokenTypes nextElement() const;

    /**
     * Function that returns the production rule used in the closure rule
     * @return const reference to the production used
     */
    const Production& getProduction() const;

    /**
     * Function that returns the origin of the closure rule
     * @return the origin of the closure rule
     */
    unsigned int getOrigin() const;
};

class Parser {
    /// Production rules used by the grammar
    std::vector<std::vector<ClosureRule>> productionRule;
public:
    /**
     * Function to construct an early parser for a given set of tokens, based on a grammar
     * @param words tokens
     * @param grammar grammar
     */
    void earleyParse(const vector<TokenTypes> &words, Grammar &grammar);

    // Todo: Git gut
    void predict(const ClosureRule &closureRule, unsigned int k, const Grammar &g);

    void scan(const ClosureRule &closureRule, unsigned int k, const vector<TokenTypes> &words);

    void complete(const ClosureRule &closureRule, unsigned int k);

    ParseTree makeTree() const;
};


#endif //RATSQL_SHUNTING_YARD_PARSER_H
