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

#ifndef RATSQL_SHUNTING_YARD_TEST_H
#define RATSQL_SHUNTING_YARD_TEST_H

#include <string>
#include "TestManager.h"

class Test {
public:
    virtual void run() = 0;

protected:
    static void expect(bool equality, std::string message);
};

#endif //RATSQL_SHUNTING_YARD_TEST_H
