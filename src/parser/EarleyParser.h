//
// Created by Maarten on 17/12/2021.
//

#ifndef RATSQL_SHUNTING_YARD_PARSER_H
#define RATSQL_SHUNTING_YARD_PARSER_H

#include <string>
#include <vector>
#include <set>
#include <memory>

#include "../datastructures/CFG.h"
#include "ParseTemplate.h"

class ParseState;

class EarleyParser {
    /// Production rules used by the grammar
    std::vector<std::vector<ParseState*>> S;
    std::shared_ptr<CFG> cfg;
public:
    /**
     * Function to construct an early parser for a given set of tokens, based on a grammar
     * @param words tokens
     * @param grammar grammar
     */
    void earleyParse(const std::vector<ParseToken> &words);

    explicit EarleyParser(std::string& grammar);
    ~EarleyParser();

    void predictor(ParseState* closureRule, unsigned int k);

    void scanner(ParseState* state, unsigned int k, const std::vector<ParseToken> &tokens);

    void completer(ParseState* closureRule, unsigned int k);
};


#endif //RATSQL_SHUNTING_YARD_PARSER_H
