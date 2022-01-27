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

#include "QueryTest.h"

#include <iostream>

void QueryTest::run() {
//    testSelection();
//    testProjection();
    testRename();
//    testMisc();
//    testNested();
}

std::string QueryTest::translate(const std::string& s) {
    const auto& tokens = mLexer->tokenise(s);
    mParser = std::make_unique<EarleyParser>(mCFG);
    const auto& tree = mParser->earleyParse(tokens);
    return tree->translate();
}

std::string QueryTest::createMessage(const string &given, const string &exp, const std::string &test) const {
    return test + " failed  - GIVEN: " + given + " - EXP: " + exp;
}

void QueryTest::testSelection() {
    std::string q1 = "σ price = 2000 (PC)";
    std::string q1_ = "sigma price = 2000 (PC)";
    std::string q1_caps = "SIGMA price = 2000 (PC)";
    std::string q1_exp = "SELECT * FROM PC WHERE price=2000";
    std::string sql_q1 = translate(q1);
    std::string sql_q1_ = translate(q1_);
    std::string sql_q1_caps = translate(q1_caps);
    QueryTest::exp_eq<std::string>(sql_q1, q1_exp, createMessage(sql_q1, q1_exp, "QueryTest::testSelection q1"));
    QueryTest::exp_eq<std::string>(sql_q1_, q1_exp, createMessage(sql_q1_, q1_exp, "QueryTest::testSelection q1_"));
    QueryTest::exp_eq<std::string>(sql_q1_caps, q1_exp, createMessage(sql_q1_caps, q1_exp, "QueryTest::testSelection q1_caps"));

    std::string q2 = "σ price = 2000 and model = 1 (PC)";
    std::string q2_ = "sigma price = 2000 and model = 1 (PC)";
    std::string q2_exp = "SELECT * FROM PC WHERE price=2000 AND model=1";
    std::string sql_q2 = translate(q2);
    std::string sql_q2_ = translate(q2_);
    QueryTest::exp_eq<std::string>(sql_q2, q2_exp, createMessage(sql_q2, q2_exp, "QueryTest::testSelection q2"));
    QueryTest::exp_eq<std::string>(sql_q2_, q2_exp, createMessage(sql_q2_, q2_exp, "QueryTest::testSelection q2_"));

    std::string q3 = "σ price > 2000 and model = 1 (PC)";
    std::string q3_ = "sigma price > 2000 and model = 1 (PC)";
    std::string q3_exp = "SELECT * FROM PC WHERE price>2000 AND model=1";
    std::string sql_q3 = translate(q3);
    std::string sql_q3_ = translate(q3_);
    QueryTest::exp_eq<std::string>(sql_q3, q3_exp, createMessage(sql_q3, q3_exp, "QueryTest::testSelection q3"));
    QueryTest::exp_eq<std::string>(sql_q3_, q3_exp, createMessage(sql_q3_, q3_exp, "QueryTest::testSelection q3_"));
}

void QueryTest::testProjection() {
    std::string q1 = "π model,speed (PC)";
    std::string q1_ = "pi model, speed (PC)";
    std::string q1_caps = "PI model,speed (PC)";
    std::string q1_exp = "SELECT model,speed FROM PC AS TempTable0";
    std::string q1__exp = "SELECT model,speed FROM PC AS TempTable1";
    std::string q1_caps_exp = "SELECT model,speed FROM PC AS TempTable2";
    std::string sql_q1 = translate(q1);
    std::string sql_q1_ = translate(q1_);
    std::string sql_q1_caps = translate(q1_caps);
    QueryTest::exp_eq<std::string>(sql_q1, q1_exp, createMessage(sql_q1, q1_exp, "QueryTest::testProjection q1"));
    QueryTest::exp_eq<std::string>(sql_q1_, q1__exp, createMessage(sql_q1_, q1__exp, "QueryTest::testProjection q1_"));
    QueryTest::exp_eq<std::string>(sql_q1_caps, q1_caps_exp, createMessage(sql_q1_caps, q1_caps_exp, "QueryTest::testProjection q1_caps"));
}

void QueryTest::testRename() {
    std::string q1 = "ρ model→m (Laptop)";
    std::string q1_ = "rho model→m (Laptop)";
    std::string q1_caps = "RHO model→m (Laptop)";
    // TODO
    std::string q1_exp = "ALTER TABLE Laptop RENAME COLUMN model TO m;";
    std::string sql_q1 = translate(q1);
    std::string sql_q1_ = translate(q1_);
    std::string sql_q1_caps = translate(q1_caps);
    QueryTest::exp_eq<std::string>(sql_q1, q1_exp, createMessage(sql_q1, q1_exp, "QueryTest::testRename q1"));
    QueryTest::exp_eq<std::string>(sql_q1_, q1_exp, createMessage(sql_q1_, q1_exp, "QueryTest::testRename q1_"));
    QueryTest::exp_eq<std::string>(sql_q1_caps, q1_exp, createMessage(sql_q1_caps, q1_exp, "QueryTest::testRename q1_caps"));
}

void QueryTest::testMisc() {
    // Cartesian Product / Join
    std::string q1 = "Laptop x PC";
    std::string q1_ = "Laptop ⨯ PC";
    // TODO
    std::string q1_exp = "SELECT * FROM Laptop, PC";
    std::string sql_q1 = translate(q1);
    std::string sql_q1_ = translate(q1_);
    QueryTest::exp_eq<std::string>(sql_q1, q1_exp, createMessage(sql_q1, q1_exp, "QueryTest::testMisc q1"));
    QueryTest::exp_eq<std::string>(sql_q1_, q1_exp, createMessage(sql_q1_, q1_exp, "QueryTest::testMisc q1_"));

    // Union
    std::string q2 = "Laptop union PC";
    std::string q2_ = "Laptop ∪ PC";
    std::string _q2 = "Laptop U PC";
    // TODO
    std::string q2_exp = "SELECT * FROM Laptop, PC";
    std::string sql_q2 = translate(q2);
    std::string sql_q2_ = translate(q2_);
    std::string _sql_q2 = translate(_q2);
    QueryTest::exp_eq<std::string>(sql_q2, q2_exp, createMessage(sql_q2, q2_exp, "QueryTest::testMisc q2"));
    QueryTest::exp_eq<std::string>(sql_q2_, q2_exp, createMessage(sql_q2_, q2_exp, "QueryTest::testMisc q2_"));
    QueryTest::exp_eq<std::string>(_sql_q2, q2_exp, createMessage(_sql_q2, q2_exp, "QueryTest::testMisc _q2"));

    // Intersect
    std::string q3 = "Laptop intersect PC";
    std::string q3_ = "Laptop ∩ PC";
    // TODO
    std::string q3_exp = "SELECT * FROM Laptop, PC";
    std::string sql_q3 = translate(q3);
    std::string sql_q3_ = translate(q3_);
    QueryTest::exp_eq<std::string>(sql_q3, q3_exp, createMessage(sql_q3, q3_exp, "QueryTest::testMisc q3"));
    QueryTest::exp_eq<std::string>(sql_q3_, q3_exp, createMessage(sql_q3_, q3_exp, "QueryTest::testMisc q3_"));
}

void QueryTest::testNested() {
    std::string q1 = "π model σ price > 2000 and ram >= 400 (PC)";
    std::string q1_exp = "SELECT model FROM PC AS TempTable0 WHERE price>2000 AND ram>=400";
    std::string sql_q1 = translate(q1);
    QueryTest::exp_eq<std::string>(sql_q1, q1_exp, createMessage(sql_q1, q1_exp, "QueryTest::testNested q1"));

    std::string q2 = "π maker σ type = 'laptop' or type = 'printer' (Product)";
    std::string q2_exp = "SELECT maker FROM Product AS TempTable0 WHERE type='laptop' OR type='printer'";
    std::string sql_q2 = translate(q2);
    QueryTest::exp_eq<std::string>(sql_q2, q2_exp, createMessage(sql_q2, q2_exp, "QueryTest::testNested q2"));

    // TODO
    std::string q3 = "model_with_price = π model, price PC ∪ π model, price Laptop ∪ π model, price Printer";
    std::string q3_exp = "CREATE VIEW AS (SELECT model, price FROM PC UNION SELECT model, price FROM Laptop UNION SELECT model, price FROM Printer)'";
    std::string sql_q3 = translate(q3);
    QueryTest::exp_eq<std::string>(sql_q3, q3_exp, createMessage(sql_q3, q3_exp, "QueryTest::testNested q3"));

    std::string q4 = "all_prices = π price (model_with_price)";
    std::string q4_exp = "CREATE VIEW all_prices AS SELECT price FROM model_with_price";
    std::string sql_q4 = translate(q4);
    QueryTest::exp_eq<std::string>(sql_q4, q4_exp, createMessage(sql_q4, q4_exp, "QueryTest::testNested q4"));

    std::string q5 = "π model (model_with_price) ⨝ (all_prices - π price σ price < price_ (all_prices ⨯ ρ price→price_ all_prices))";
    std::string q5_exp = "";
    std::string sql_q5 = translate(q5);
    QueryTest::exp_eq<std::string>(sql_q5, q5_exp, createMessage(sql_q5, q5_exp, "QueryTest::testNested q5"));
}