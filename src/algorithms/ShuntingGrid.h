//
// Created by robnoo on 27/01/22.
//

#ifndef RATSQL_PARSING_SHUNTINGGRID_H
#define RATSQL_PARSING_SHUNTINGGRID_H


#include <vector>
#include "../parser/ParseTemplate.h"

/**
 * @class ShuntingGrid
 * @brief Shunting grid - part of the shunting yard algorithm
 */
class ShuntingGrid {
private:
    /// Grid with all the parse tokens
    std::vector<std::vector<ParseToken>> grid;
    /// Indicator for the usages of a certain vector of parse tokens
    std::vector<int> usages;
    /**
     * @brief Will calculate the usages of a certain vector with parse tokens and store it in 'usages'
     */
    void calculateUsages();
public:
    /**
     * @brief Will add an expression to the grid
     * @param t1    first element in vector
     * @param t2    second element in vector
     * @param t3    third element in vector
     * @return      Index where the expression is placed
     */
    int addExpression(ParseToken& t1, ParseToken& t2, ParseToken& t3);
    /**
     * @brief Will substitute any  elements that have more than one usage
     * @return      The resulted vector with the substitutions done
     */
    std::vector<std::vector<ParseToken>> substitute();
    /**
     * Will substitute a current based on its usages and row
     * @param current       current vector with parse tokens
     * @param row           current row
     */
    void substitute(vector<ParseToken> &current, int row);
};


#endif //RATSQL_PARSING_SHUNTINGGRID_H
