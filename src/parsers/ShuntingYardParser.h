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

    std::set<std::string> tokens = {"π", "σ", "⋈", "∪", "∩", "-", "(", ")"};

    void consumeOperator(std::string& opSymbol);
    void consumeText(std::string& text);
};


#endif //RATSQL_SHUNTINGYARDPARSER_H
