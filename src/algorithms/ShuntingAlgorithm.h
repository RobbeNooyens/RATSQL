//
// Created by Cédric Leclercq on 25/11/2021.
//

#ifndef RATSQL_SHUNTINGALGORITHM_H
#define RATSQL_SHUNTINGALGORITHM_H

#include <string>
#include <vector>
#include "../parsers/ShuntingYardParser.h"

class ShuntingAlgorithm {
public:
    ShuntingAlgorithm()=default;
    void operator()(std::string& str);

private:
    ShuntingYardParser parser;
};


#endif //RATSQL_SHUNTINGALGORITHM_H
