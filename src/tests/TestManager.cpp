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

#include <iostream>
#include "TestManager.h"
#include "Test.h"

using namespace std;

void TestManager::testFailed(std::string &message) {
    cout << message << endl;
}

void TestManager::runTests() {
    for(auto& test: TestManager::getInstance().tests) {
        test->run();
    }
}

TestManager &TestManager::getInstance() {
    static TestManager INSTANCE;
    return INSTANCE;
}

TestManager::TestManager() = default;
