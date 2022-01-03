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

class ShuntingYardTest: public Test {
public:
    void run() override;
    static void testExpectedOutput();
};


#endif //RATSQL_SHUNTING_YARD_SHUNTINGYARDTEST_H
