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

#include "LevenshteinTest.h"
#include "ShuntingYardTest.h"
#include "QueryTest.h"

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

void TestManager::initiateTests() {
    this->tests.push_back(std::make_unique<LevenshteinTest>());
    this->tests.push_back(std::make_unique<ShuntingYardTest>());
    this->tests.push_back(std::make_unique<QueryTest>());
}

TestManager::TestManager() {
    this->initiateTests();
}
