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

#ifndef RATSQL_SHUNTING_YARD_LEVENSHTEINTEST_H
#define RATSQL_SHUNTING_YARD_LEVENSHTEINTEST_H

#include "Test.h"

class LevenshteinTest: public Test {
public:
    void run() override;

    static void testDistance();
    static void testIdentical();
    static void testNotIdentical();
};


#endif //RATSQL_SHUNTING_YARD_LEVENSHTEINTEST_H
