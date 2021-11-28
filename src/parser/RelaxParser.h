//
// Created by Maarten on 28/11/2021.
//

#ifndef RATSQL_RELAXPARSER_H
#define RATSQL_RELAXPARSER_H

#include <string>
#include <vector>
#include <fstream>

class RelaxParser {
private:
    const char delimiter = '\\';

public:
    RelaxParser(const std::string &parseString);
};


#endif //RATSQL_RELAXPARSER_H
