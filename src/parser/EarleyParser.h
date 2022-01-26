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
#include "TreeNode.h"

class ParseState;

class EarleyParser {
    /// Production rules used by the grammar
    std::vector<std::vector<ParseState*>> S;
    std::shared_ptr<CFG> cfg;
public:
    /**
     * Function to construct an early parser for a given set of tokens, based on a grammar
     * @param tokens tokens
     * @param grammar grammar
     */
    TreeNode * earleyParse(const std::vector<ParseToken> &tokens);

    explicit EarleyParser(std::string& grammar);

    /**
     * Constructor for EarlyParser
     * @param cfg pointer to the grammar
     */
    explicit EarleyParser(const std::shared_ptr<CFG> &cfg);

    ~EarleyParser();

    void predictor(ParseState* closureRule, unsigned int k);

    void scanner(ParseState* state, unsigned int k, const std::vector<ParseToken> &tokens);

    void completer(ParseState* closureRule, unsigned int k);
};


#endif //RATSQL_SHUNTING_YARD_PARSER_H
