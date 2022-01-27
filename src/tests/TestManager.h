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

#ifndef RATSQL_SHUNTING_YARD_TESTMANAGER_H
#define RATSQL_SHUNTING_YARD_TESTMANAGER_H


#include <string>
#include <vector>
#include <memory>

class Test;
/**
 * @class TestManager
 * @brief Manager for tests implemented using Singleton design pattern
 */
class TestManager {
public:
    /**
     * @brief Display error message when tests failed
     * @param message std::string - error message
     */
    static void testFailed(std::string& message);
    /**
     * @brief Run tests
     */
    static void runTests();
private:
    /**
     * @brief Get instance of TestManager
     * @return static TestManager instance by reference
     */
    static TestManager& getInstance();
    /**
     * @brief Default constructor for TestManager object
     */
    TestManager();
    /**
     * @brief Initiate tests
     */
    void initiateTests();

    /// @brief std::vector<Test> - std::vector of unique pointers to Tests
    std::vector<std::unique_ptr<Test>> tests;
};


#endif //RATSQL_SHUNTING_YARD_TESTMANAGER_H
