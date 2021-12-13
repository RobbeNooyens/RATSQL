/**
 *  ╒══════════════════════════════════════════════════╕
 *  │                                                  │
 *  │                 RATSQL Project                   │
 *  │            Relational Algebra To SQL             │
 *  │                                                  │
 *  │  Contributors: Pablo Deputter, Cédric Leclercq,  │
 *  │               Robbe Nooyens, Maarten Peirsman    │
 *  │                                                  │
 *  │   University of Antwerp - Advanced Programming   │
 *  │                                                  │
 *  ╘══════════════════════════════════════════════════╛
 */

#ifndef RATSQL_SHUNTING_YARD_TESTMANAGER_H
#define RATSQL_SHUNTING_YARD_TESTMANAGER_H


#include <string>
#include <vector>
#include <memory>

class Test;

class TestManager {
public:
    static void testFailed(std::string& message);
    static void runTests();

private:
    static TestManager& getInstance();
    TestManager();
    std::vector<std::unique_ptr<Test>> tests;

};


#endif //RATSQL_SHUNTING_YARD_TESTMANAGER_H
