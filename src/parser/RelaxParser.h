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
    const char delimiter = ' ';

public:
    /**
     * Constructor for Relax Parser
     * @param parseString string to parse
     */
    RelaxParser(const std::string &parseString);

    /**
     * Function to split strings on " "
     * @param parseString string to split
     * @return vector with split parts
     */
    std::vector<std::string> splitString(const std::string &parseString);
};


#endif //RATSQL_RELAXPARSER_H
