//
// Created by Cédric Leclercq on 29/11/2021.
//

#ifndef RATSQL_SHUNTINGYARDPARSER_H
#define RATSQL_SHUNTINGYARDPARSER_H

#include<vector>
#include<string>
#include <set>

class ShuntingYardParser {
public:
    ShuntingYardParser();

    void consume(std::string& symbol);
    void flush();

private:
    std::vector<std::string> stack;

    std::set<std::string> tokens = {"π", "σ", "⋈", "∪", "∩", "-", "(", ")"};

    void consumeOperator();
    void consumeText();
};


#endif //RATSQL_SHUNTINGYARDPARSER_H
