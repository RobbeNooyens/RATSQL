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

class ParseState {
public:
    ParseState();
    ParseState(ProductionRule production, int dot, int origin);

    const ProductionRule& getProduction();
    int getDot() const;
    int getOrigin() const;

    const std::string& nextElement();

    bool isFinished();

    std::string toString();

//    bool operator==(const ParseState& rhs);
//    bool operator!=(const ParseState& rhs);

    bool operator==(ParseState& rhs);
    bool operator!=(ParseState& rhs);


private:
    ProductionRule production;
    int dot = 0;
    int origin = 0;

};

class Parser {
    /// Production rules used by the grammar
    std::vector<std::vector<ParseState>> S;
    std::unique_ptr<CFG> cfg;
public:
    /**
     * Function to construct an early parser for a given set of tokens, based on a grammar
     * @param words tokens
     * @param grammar grammar
     */
    void earleyParse(const std::vector<std::string> &words);

    Parser();

    // Todo: Git gut
    void predictor(ParseState &closureRule, unsigned int k);

    void scanner(ParseState &closureRule, unsigned int k, const std::vector<std::string> &words);

    void completer(ParseState &closureRule, unsigned int k);
};


#endif //RATSQL_SHUNTING_YARD_PARSER_H
