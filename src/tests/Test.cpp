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

#include "Test.h"

/*
template<typename T>
void Test::exp_eq(const T &t1, const T &t2, std::string message) {
    if (t1 != t2) {
        TestManager::testFailed(message);
    }
}


template<typename T>
void Test::exp_neq(const T &t1, const T &t2, std::string message) {
    if (t1 == t2) {
        TestManager::testFailed(message);
    }
}
*/

void Test::exp_eq_int(int p1, int p2, std::string message) {
    if (p1 != p2) {
        TestManager::testFailed(message);
    }
}

