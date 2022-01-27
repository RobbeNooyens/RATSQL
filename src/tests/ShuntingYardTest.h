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

#ifndef RATSQL_SHUNTING_YARD_SHUNTINGYARDTEST_H
#define RATSQL_SHUNTING_YARD_SHUNTINGYARDTEST_H


#include "Test.h"
#include "../algorithms/ShuntingAlgorithm.h"

/**
 * @class ShuntingYardTest
 * @brief ShuntingYardTest derived from Test
 */
class ShuntingYardTest: public Test {
public:
    /**
     * @brief Run tests
     */
    void run() override;
    /**
     * @brief Virtual default destructor
     */
    virtual ~ShuntingYardTest() = default;
    /**
     * @brief Test ShuntingYard-algorithm
     */
    static void testExpectedOutput();
};


#endif //RATSQL_SHUNTING_YARD_SHUNTINGYARDTEST_H
