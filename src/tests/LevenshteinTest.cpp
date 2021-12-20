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

#include "LevenshteinTest.h"
#include "../algorithms/LevenshteinDistance.h"

#include <iostream>

void LevenshteinTest::run() {
    LevenshteinTest::testDistance();
    LevenshteinTest::testIdentical();
    LevenshteinTest::testNotIdentical();
}

void LevenshteinTest::testDistance() {
    /*
     * Comparing every str A to variants in every test
     */

    // Test 1: "hello"
    std::string str1A = "hello", str1B = "hello", str1C = "helol", str1D = "delel";
    int eval1AB = LevenshteinDistance::evalLevenshteinDistance(str1A,str1B);
    int eval1AC = LevenshteinDistance::evalLevenshteinDistance(str1A,str1C);
    int eval1AD = LevenshteinDistance::evalLevenshteinDistance(str1A,str1D);
    LevenshteinTest::exp_eq_int(eval1AB,1,"LevenshteinTest::testDistance str1A x str1B distance test failed.");
    LevenshteinTest::exp_eq_int(eval1AC,1,"LevenshteinTest::testDistance str1A x str1C distance test failed.");
    LevenshteinTest::exp_eq_int(eval1AD,0,"LevenshteinTest::testDistance str1A x str1D distance test failed.");

    // Test 2: "The quick brown fox jumps over the lazy dog"
    std::string str2A = "The quick brown fox jumps over the lazy dog";
    std::string str2B = "The quick brond fox jumps over the lazy dog"; // Testing replacement
    std::string str2C = "The quick brown fox jumps over the lazy"; // Testing missing characters
    std::string str2D = "The quick brown fox ujmps over the lazy dog"; // Testing switching two chars
    std::string str2E = "The quick brown fox jumps over thed lazy dog"; // Testing removal of characters
    int eval2AB = LevenshteinDistance::evalLevenshteinDistance(str2A, str2B,0);
    int eval2AC = LevenshteinDistance::evalLevenshteinDistance(str2A, str2C,4);
    int eval2AD = LevenshteinDistance::evalLevenshteinDistance(str2A, str2D,0);
    int eval2AE = LevenshteinDistance::evalLevenshteinDistance(str2A, str2E,1);
    LevenshteinTest::exp_eq_int(eval2AB,0,"LevenshteinTest::testDistance str2A x str2B distance test failed.");
    LevenshteinTest::exp_eq_int(eval2AC,1,"LevenshteinTest::testDistance str2A x str2C distance test failed.");
    LevenshteinTest::exp_eq_int(eval2AD,0,"LevenshteinTest::testDistance str2A x str2D distance test failed.");
    LevenshteinTest::exp_eq_int(eval2AE,1,"LevenshteinTest::testDistance str2A x str2E distance test failed.");
}

void LevenshteinTest::testIdentical() {
    std::string str1A = "This RATSQL project is so cool!";
    std::string str1B = "This RATSQL project is so cool!";
    int eval1AB = LevenshteinDistance::evalLevenshteinDistance(str1A,str1B,0);
    LevenshteinTest::exp_eq_int(eval1AB,1,"LevenshteinTest::testIdentical str1A x str1B distance test failed.");
}

void LevenshteinTest::testNotIdentical() {
    std::string str1A = "This RATSQL project is so cool!";
    std::string str1B = "This RATSQL project is not cool!";
    int eval1AB = LevenshteinDistance::evalLevenshteinDistance(str1A,str1B,0);
    LevenshteinTest::exp_eq_int(eval1AB,0,"LevenshteinTest::testNotIdentical str1A x str1B distance test failed.");
}
