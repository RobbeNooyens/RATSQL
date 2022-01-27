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

class QueryTest : public Test {

public:
    QueryTest() : Test() { mSystem = std::make_unique<System>(); }

    void run() override;

    void testSelection();

    void testProjection();

    void testRename();

    void testMisc();

    void testNested();

    virtual ~QueryTest() = default;

private:
    std::unique_ptr<System> mSystem;

    std::string createMessage(const std::string& given, const std::string& exp, const std::string& test) const;
};


#endif //RATSQL_PARSING_QUERYTEST_H
