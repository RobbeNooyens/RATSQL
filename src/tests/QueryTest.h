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

#ifndef RATSQL_PARSING_QUERYTEST_H
#define RATSQL_PARSING_QUERYTEST_H

#include "Test.h"
#include "../system/System.h"

#include <memory>

/**
 * @class QueryTest
 * @brief QueryTest derived from Test to test parser and query conversion functionalities
 */
class QueryTest : public Test {
public:
    /**
     * @brief Construct QueryTest object
     */
    QueryTest() : Test() { mSystem = std::make_unique<System>(); }
    /**
     * @brief Run tests
     */
    void run() override;
    /**
     * @brief Test selection operator
     */
    void testSelection();
    /**
     * @brief Test projection operator
     */
    void testProjection();
    /**
     * @brief Test rename operator
     */
    void testRename();
    /**
     * @brief Test miscellaneous queries
     */
    void testMisc();
    /**
     * @brief Test nested queries
     */
    void testNested();
    /**
     * @brief Default destructor for QueryTest object
     */
    virtual ~QueryTest() = default;
private:
    /// @brief Unique pointer to system
    std::unique_ptr<System> mSystem;
    /**
     * @brief Create error message for given inputs
     * @param given std::string - given query output
     * @param exp std::string - expected query output
     * @param test std::string - what test was running
     * @return std::string - error message
     */
    std::string createMessage(const std::string& given, const std::string& exp, const std::string& test) const;
};


#endif //RATSQL_PARSING_QUERYTEST_H
