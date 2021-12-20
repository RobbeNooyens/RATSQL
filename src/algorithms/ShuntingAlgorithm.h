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

#include <string>
#include <vector>
#include "../parsers/ShuntingYardParser.h"

class ShuntingAlgorithm {
public:
    ShuntingAlgorithm()=default;
    void operator()(std::string& str, std::ostream& stream=std::cout);
    ShuntingYardParser getParser() const;
protected:
    ShuntingYardParser parser;
};


#endif //RATSQL_SHUNTINGALGORITHM_H
