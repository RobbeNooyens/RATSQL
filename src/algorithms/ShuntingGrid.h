//
// Created by robnoo on 27/01/22.
//

#ifndef RATSQL_PARSING_SHUNTINGGRID_H
#define RATSQL_PARSING_SHUNTINGGRID_H


#include <vector>
#include "../parser/ParseTemplate.h"

class ShuntingGrid {
private:
    std::vector<std::vector<ParseToken>> grid;
    std::vector<int> usages;

    void calculateUsages();
public:
    int addExpression(ParseToken& t1, ParseToken& t2, ParseToken& t3);
    std::vector<std::vector<ParseToken>> substitute();

    void substitute(vector<ParseToken> &current, int row);
};


#endif //RATSQL_PARSING_SHUNTINGGRID_H
