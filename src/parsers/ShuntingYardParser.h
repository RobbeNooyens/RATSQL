//
// Created by Cédric Leclercq on 29/11/2021.
//

#ifndef RATSQL_SHUNTINGYARDPARSER_H
#define RATSQL_SHUNTINGYARDPARSER_H

#include<vector>
#include<string>
#include <set>
#include <stack>
#include <queue>
#include <map>

class ShuntingYardParser {
public:
    ShuntingYardParser();

    void printOperatorStack();
    void printQueue();

    void consume(std::string& symbol);
    void flush();

private:
    std::stack<std::string> operatorStack;
    std::queue<std::string> queue;

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

    void consumeOperator(std::string& opSymbol);
    void consumeText(std::string& text);
};


#endif //RATSQL_SHUNTINGYARDPARSER_H
