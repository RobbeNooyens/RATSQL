//
// Created by Cédric Leclercq on 29/11/2021.
//

#ifndef RATSQL_SHUNTINGYARDPARSER_H
#define RATSQL_SHUNTINGYARDPARSER_H

#include<vector>
#include<string>

class ShuntingYardParser {
public:
    ShuntingYardParser();

    void consume(std::string& symbol);

private:
    std::vector<std::string> stack;

    void consumeOperator();
    void consumeText();
};


#endif //RATSQL_SHUNTINGYARDPARSER_H
