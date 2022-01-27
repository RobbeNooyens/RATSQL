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

// TODO - doen via Cedric zijn klasse?
#include "../parser/EarleyParser.h"
#include "../parser/Lexer.h"
#include "../datastructures/CFG.h"

#include <memory>

class QueryTest : public Test {

public:
    QueryTest() : Test() {
        mCFG = std::make_shared<CFG>("input/grammar.json");
        mLexer = std::make_unique<Lexer>(mCFG->getAliasMap(), mCFG->getAliases());
        mParser = std::make_unique<EarleyParser>(mCFG);
    }

    void run() override;

    void testSelection();

    void testProjection();

    void testRename();

    void testMisc();

    void testNested();

    virtual ~QueryTest() = default;

private:
    std::shared_ptr<CFG> mCFG;
    std::unique_ptr<Lexer> mLexer;
    std::unique_ptr<EarleyParser> mParser;

    std::string translate(const std::string& s);

    std::string createMessage(const std::string& given, const std::string& exp, const std::string& test) const;
};


#endif //RATSQL_PARSING_QUERYTEST_H
