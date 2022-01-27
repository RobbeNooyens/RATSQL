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

/**
 * @class LevenshteinTest
 * @brief ShuntingYardTest derived from Test
 */
class LevenshteinTest: public Test {
public:
    /**
     * @brief Run tests
     */
    void run() override;
    /**
     * @brief Virtual default destructor
     */
    virtual ~LevenshteinTest() = default;
    /**
     * @brief Test if Levenshtein algorithm gives the correct output for a variety of strings
     */
    static void testDistance();
    /**
     * Test if Levenshtein algorithm gives correct output for identical strings
     */
    static void testIdentical();
    /**
     * Test if Levenshtein algorithm gives correct output for non-identical strings
     */
    static void testNotIdentical();
};


#endif //RATSQL_SHUNTING_YARD_LEVENSHTEINTEST_H
