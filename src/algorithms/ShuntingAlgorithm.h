//
// Created by Cédric Leclercq on 25/11/2021.
//

#ifndef RATSQL_SHUNTINGALGORITHM_H
#define RATSQL_SHUNTINGALGORITHM_H

#include <string>
#include <vector>

class ShuntingAlgorithm {
public:
    ShuntingAlgorithm()=default;
    std::string operator()();

private:
    std::vector<std::string> stack;

};


#endif //RATSQL_SHUNTINGALGORITHM_H
