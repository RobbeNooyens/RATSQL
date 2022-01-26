/**
 *  ╒═══════════════════════════════════════════════════════════╕
 *  │                                                           │
 *  │                     RATSQL Project                        │
 *  │                Relational Algebra To SQL                  │
 *  │                                                           │
 *  │       Contributors: Pablo Deputter, Cédric Leclercq,      │
 *  │                     Robbe Nooyens, Maarten Peirsman       │
 *  │                                                           │
 *  │    University of Antwerp - Machines en Berekenbaarheid    │
 *  │                                                           │
 *  ╘═══════════════════════════════════════════════════════════╛
 */

#ifndef RATSQL_SHUNTINGALGORITHM_H
#define RATSQL_SHUNTINGALGORITHM_H

#include<vector>
#include<string>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <iostream>
#include "../datastructures/RAExpression.h"
#include "../parser/Tokens.h"
#include "../parser/ParseTemplate.h"

enum OperatorType {PREFIX, INFIX, POSTFIX};

class ParseToken;

/**
 * @class ShuntingAlgorithm
 * @isFriendOf ShuntingYardParser
 */
class ShuntingAlgorithm {
public:
    /**
     * @brief Default constructor
     */
    ShuntingAlgorithm()=default;
    /**
     * @brief Apply the shunting algorithm by the operator()
     * @param str       str for the algorithm to apply on
     * @param stream    ostream for the output
     */
    void operator()(std::vector<ParseToken>& tokens, std::ostream& stream=std::cout);
    /**
     * @brief Will parse the input, create an expression, and possibly print the result
     * @param stream    to which stream to print - default is cout
     * @param print     print the result - default is true
     * @return
     */
    RAExpression parse(std::ostream& stream=std::cout, bool print=true);
    /**
     * @brief Getter for the RA expression
     * @return
     */
    RAExpression getRAExpression() const;
private:
    /// @brief Stack with all the operators
    std::stack<ParseToken> operatorStack{};
    /// @brief Main queue with the full string expression
    std::queue<ParseToken> queue{};
    /// @brief Stack with all the non-operator variables
    std::stack<ParseToken> textStack{};
    /// @brief The relational expression that the pars() function returns
    RAExpression expression{};
    /// @brief Demonstrates an empty string
    ParseToken emptyToken{"", ""};
    /// @brief Map with the precedence of all the operators
    std::map<std::string, int> precedence = {
            {Tokens::PI, 2},
            {Tokens::SIGMA, 3},
            {Tokens::RHO, 4},

            {Tokens::JOIN, 10},
            {Tokens::UNION, 10},
            {Tokens::INTERSECT, 10},
            {Tokens::SUBTRACT, 10},
            {Tokens::SCALAR, 10},
            {Tokens::DOT, 10},

            {Tokens::ROUNDED_BRACKET_LEFT, 20},
            {Tokens::ROUNDED_BRACKET_RIGHT, 20},

            {Tokens::AND, 2},
            {Tokens::OR, 2},
            {Tokens::NOT, 2},

            {Tokens::EQUALS, 1},
            {Tokens::NOT_EQUALS, 1},
            {Tokens::LESS_THAN_OR_EQUALS, 1},
            {Tokens::GREATER_THAN_OR_EQUALS, 1},
            {Tokens::LESS_THAN, 1},
            {Tokens::GREATER_THAN, 1},
            {Tokens::COMMA, 1},
            {Tokens::ARROW_LEFT, 1},
            {Tokens::ARROW_RIGHT, 1},
    };
    /// @brief Map with all the kind of notations of all the operators
    std::map<std::string, OperatorType> operatorTypes = {
            {Tokens::PI, PREFIX},
            {Tokens::SIGMA, PREFIX},
            {Tokens::RHO, PREFIX},

            {Tokens::AND, INFIX},
            {Tokens::OR, INFIX},
            {Tokens::NOT, INFIX},

            {Tokens::JOIN, INFIX},
            {Tokens::UNION, INFIX},
            {Tokens::INTERSECT, INFIX},
            {Tokens::SUBTRACT, INFIX},

            {Tokens::EQUALS, INFIX},
            {Tokens::NOT_EQUALS, INFIX},
            {Tokens::GREATER_THAN_OR_EQUALS, INFIX},
            {Tokens::LESS_THAN_OR_EQUALS, INFIX},
            {Tokens::LESS_THAN_OR_EQUALS, INFIX},
            {Tokens::LESS_THAN, INFIX},
            {Tokens::GREATER_THAN, INFIX},
            {Tokens::COMMA, INFIX},
            {Tokens::ARROW_LEFT, INFIX},
    };
    /**
     * @brief Will flush the stack and create a new expression
     */
    void flush();
    /**
     * @brief Getter for the top of the stack
     * @return      stack top
     */
    ParseToken & getStackTop();
    /**
     * @brief Simple printing function for the operator stack
     */
    __attribute__((unused)) void printOperatorStack();
    /**
     * @brief Simple printing function fot the current queue
     */
    __attribute__((unused)) void printQueue();
    /**
     * @brief Checks if a given symbol is an operator or not
     * @param symbol    symbol to check
     * @return      operator?
     */
    bool isOperator(ParseToken &symbol);
    /**
     * @brief Will consume an operator pre-parsing
     * @param opSymbol  toConsume
     */
    void consumeOperator(ParseToken &opSymbol);
    /**
     * @brief Will consume a non-operator pre-parsing
     * @param text      toConsume
     */
    void consumeText(ParseToken &text);
    /**
     * @brief will parse a certain operator during the parse() function
     * @note Changes the expression of the class (and clears the previous expression)
     * @param queueFront    current front of the queue
     * @param output        a vector for storing all the results (for later printing)
     * @note Adds RA words to the expression
     */
    void parseOperator(ParseToken &queueFront, std::vector<std::string>& output);
};


#endif //RATSQL_SHUNTINGALGORITHM_H
