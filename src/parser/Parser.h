//
// Created by Maarten on 17/12/2021.
//

#ifndef RATSQL_SHUNTING_YARD_PARSER_H
#define RATSQL_SHUNTING_YARD_PARSER_H

#include <string>
#include <vector>

#include "Grammar.h"

class ClosureRule {
    /// Production on which the closure is based
    Production production;

    /// Position of the closure
    unsigned int closure;

public:
    /**
     * Constructor for closure rule
     * @param p production used to make the closure rule
     * @param c index of the closure (0 by default)
     */
    ClosureRule(const Production &p, unsigned int c = 0);
};

class Parser {
    /// Production rules used by the grammar
    std::vector<Production> productionRule;
public:
    /**
     * Function to construct an early parser for a given set of words, based on a grammar
     * @param words
     * @param grammar
     */
    void earlyParse(std::vector<std::string> &words, const Grammar &grammar);
};


#endif //RATSQL_SHUNTING_YARD_PARSER_H
