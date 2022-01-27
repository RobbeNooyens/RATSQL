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

#include "ShuntingYardTest.h"

void ShuntingYardTest::run() {
    ShuntingYardTest::testExpectedOutput();
}

void ShuntingYardTest::testExpectedOutput() {
    std::string input1 = "σ maker2 < maker ( ρ maker2 ← maker π maker, type Product ⋈ π maker, type Product )";
    ShuntingAlgorithm shunting;
//    shunting(input1);
    //shunting.getParser().parse();
    //RAExpression exp = shunting.getParser().getRAExpression();
    //std::vector<RAWord> expVector = exp.getExpression();
    std::string error = "ShuntingYardTest::testExpectedOutput failed.";
    //for (int it = 0; it < expVector.size(); it++) {
        //switch(it) {
            //case 0: if (!(expVector[it] != "π maker,type Product")) TestManager::testFailed(error);
            //case 1: if (!(expVector[it] != "ρ maker2←maker 0")) TestManager::testFailed(error);
            //case 2: if (!(expVector[it] != "1 ⋈ 0")) TestManager::testFailed(error);
            //case 3: if (!(expVector[it] != "σ maker2<maker 2")) TestManager::testFailed(error);
            //default: TestManager::testFailed(error); // Default should never happen!
        //}
    //}
}
