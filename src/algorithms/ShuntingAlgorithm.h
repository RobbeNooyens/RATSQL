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

/**
 * @class ShuntingAlgorithm
 * @isFriendOf ShuntingYardParser
 */
class ShuntingAlgorithm {
public:
    /**
     * @brief Default constructor
     */
    ShuntingAlgorithm()=default;
    /**
     * @brief Apply the shunting algorithm by the operator()
     * @param str       str for the algorithm to apply on
     * @param stream    ostream for the output
     */
    void operator()(std::string& str, std::ostream& stream=std::cout);
    /**
     * @brief Getter for the output
     * @return      parser
     */
    ShuntingYardParser getParser() const;
protected: // todo bad practice to use protected - change?
    ShuntingYardParser SAParser;
};


#endif //RATSQL_SHUNTINGALGORITHM_H
