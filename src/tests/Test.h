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

/**
 * @class Test
 * @brief Abstract class implemented for Tests
 */
class Test {
public:
    /**
     * @brief Abstract member to run tests
     */
    virtual void run() = 0;
    /**
     * @brief Virtual default destructor
     */
    virtual ~Test() = default;
protected:
    /**
     * @brief Check if 2 given ints are equal, when not display an error message
     * @param p1 int - first int
     * @param p2 int - second int
     * @param message std::string - message to be displayed when two ints are not equal
     */
    static void exp_eq_int(int p1, int p2, std::string message);
    /**
     * @brief Check if two given objects of class T are equal, when not display an error message
     * @tparam T template parameter used in member function
     * @param t1 T - first object
     * @param t2 T - second object
     * @param message td::string - message to be displayed when two object are not equal
     */
    template<typename T>
    static void exp_eq(const T &t1, const T &t2, std::string message) {
        if (t1 != t2) {
            TestManager::testFailed(message);
        }
    }
    /**
     * @brief Check if two given objects of class T are not equal, when not display an error message
     * @tparam T template parameter used in member function
     * @param t1 T - first object
     * @param t2 T - second object
     * @param message td::string - message to be displayed when two object are equal
     */
    template<typename T>
    static void exp_neq(const T &t1, const T &t2, std::string message) {
        if (t1 == t2) {
            TestManager::testFailed(message);
        }
    }
};

#endif //RATSQL_SHUNTING_YARD_TEST_H
