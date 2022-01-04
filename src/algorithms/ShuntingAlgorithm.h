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
enum OperatorType {PREFIX, INFIX, POSTFIX};

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
    void operator()(std::string& str, std::ostream& stream=std::cout);
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
    std::stack<std::string> operatorStack{};
    /// @brief Main queue with the full string expression
    std::queue<std::string> queue{};
    /// @brief Stack with all the non-operator variables
    std::stack<std::string> textStack{};
    /// @brief The relational expression that the pars() function returns
    RAExpression expression{};
    /// @brief Demonstrates an empty string
    std::string emptyString{};
    /// @brief Map with the precedence of all the operators
    std::map<std::string, int> precedence = {
            {"π", 2},
            {"σ", 1},
            {"⋈", 10},
            {"∪", 1},
            {"∩", 1},
            {"-", 1},
            {"ρ", 3},
            {"(", 20},
            {")", 20}
    };
    /// @brief Map with all the kind of notations of all the operators
    std::map<std::string, OperatorType> operatorTypes = {
            {"π", PREFIX},
            {"σ", PREFIX},
            {"⋈", INFIX},
            {"∪", INFIX},
            {"∩", INFIX},
            {"-", INFIX},
            {"ρ", PREFIX}
    };
    /**
     * @brief Will consume an input (needs to be done before parsing)
     * @param symbol
     */
    void consume(std::string& symbol);
    /**
     * @brief Will flush the stack and create a new expression
     */
    void flush();
    /**
     * @brief Getter for the top of the stack
     * @return      stack top
     */
    std::string& getStackTop();
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
    bool isOperator(std::string& symbol);
    /**
     * @brief Will consume an operator pre-parsing
     * @param opSymbol  toConsume
     */
    void consumeOperator(std::string& opSymbol);
    /**
     * @brief Will consume a non-operator pre-parsing
     * @param text      toConsume
     */
    void consumeText(std::string& text);
    /**
     * @brief will parse a certain operator during the parse() function
     * @note Changes the expression of the class (and clears the previous expression)
     * @param queueFront    current front of the queue
     * @param output        a vector for storing all the results (for later printing)
     * @note Adds RA words to the expression
     */
    void parseOperator(std::string& queueFront, std::vector<std::string>& output);
};


#endif //RATSQL_SHUNTINGALGORITHM_H
