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

/**
 * @class EarleyParser
 * @brief An implementation of a fully working earley parser
 */
class EarleyParser {
    /// @brief Production rules used by the grammar
    std::vector<std::vector<ParseState*>> S;
    /// @brief Shared pointer to a CFG
    std::shared_ptr<CFG> cfg;
public:
    /**
     * @brief Function to construct an early parser for a given set of tokens, based on a grammar
     * @param tokens tokens
     * @param grammar grammar
     */
    TreeNode * earleyParse(const std::vector<ParseToken> &tokens);
    /**
     * @brief Explicit constructor for the earley parser
     * @param grammar   grammar to construct the parser with
     */
    explicit EarleyParser(std::string& grammar);

    /**
     * @brief Constructor for EarlyParser
     * @param cfg pointer to the grammar
     */
    explicit EarleyParser(const std::shared_ptr<CFG> &cfg);
    /**
     * @brief Destructor for the earley parser
     */
    ~EarleyParser();
    /**
     * @brief Predictor for the parser
     * @param closureRule   The closure rule for the predictor
     * @param k             The set where you need to input
     */
    void predictor(ParseState* closureRule, unsigned int k);
    /**
     * @brief Scanner for the parser
     * @param state         state to scan
     * @param k             The set to input in
     * @param tokens        Tokens to use
     */
    void scanner(ParseState* state, unsigned int k, const std::vector<ParseToken> &tokens);
    /**
     * @brief Completer for the parser
     * @param closureRule   The closure rule for the completer
     * @param k             The set where you need to input
     */
    void completer(ParseState* closureRule, unsigned int k);
};


#endif //RATSQL_SHUNTING_YARD_PARSER_H
