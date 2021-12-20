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

#ifndef RATSQL_SHUNTINGYARDPARSER_H
#define RATSQL_SHUNTINGYARDPARSER_H

#include<vector>
#include<string>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <iostream>
#include "../datastructures/RAExpression.h"

enum OperatorType {PREFIX, INFIX, POSTFIX};

class ShuntingYardParser {
public:
    ShuntingYardParser() = default;

    void printOperatorStack();
    void printQueue();

    void consume(std::string& symbol);
    void flush();
    void generateOutput(std::ostream& stream=std::cout, bool print=true, bool saveExpression=false);
    void generateOutput(bool saveExpression, bool print=true, std::ostream& stream=std::cout);
    RAExpression getRAExpression() const;

private:
    std::stack<std::string> operatorStack;
    std::queue<std::string> queue;
    std::stack<std::string> textStack;
    RAExpression expression{};

    std::string emptyStack;
    std::string& getStackTop();


    bool isOperator(std::string& symbol);
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

    std::map<std::string, OperatorType> operatorTypes = {
            {"π", PREFIX},
            {"σ", PREFIX},
            {"⋈", INFIX},
            {"∪", INFIX},
            {"∩", INFIX},
            {"-", INFIX},
            {"ρ", PREFIX}
    };

    void consumeOperator(std::string& opSymbol);
    void consumeText(std::string& text);

};


#endif //RATSQL_SHUNTINGYARDPARSER_H
