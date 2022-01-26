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
#include "algorithms/LevenshteinDistance.h"
#include "algorithms/ShuntingAlgorithm.h"
#include "parser/Lexer.h"
#include "parser/Tokens.h"

int main(int argc, char* argv[]) {
    std::vector<ParseToken> tokens = {
            {Tokens::SIGMA, "σ"},
            {Tokens::NAME, "maker2"},
            {Tokens::LESS_THAN, "<"},
            {Tokens::NAME, "maker"},
            {Tokens::ROUNDED_BRACKET_LEFT, "("},
            {Tokens::RHO, "ρ"},
            {Tokens::NAME, "maker2"},
            {Tokens::ARROW_LEFT, "<-"},
            {Tokens::NAME, "maker"},
            {Tokens::PI, "π"},
            {Tokens::NAME, "maker"},
            {Tokens::COMMA, ","},
            {Tokens::NAME, "type"},
            {Tokens::ROUNDED_BRACKET_LEFT, "("},
            {Tokens::NAME, "Product"},
            {Tokens::ROUNDED_BRACKET_RIGHT, ")"},
            {Tokens::UNION, "U"},
            {Tokens::PI, "π"},
            {Tokens::NAME, "maker"},
            {Tokens::COMMA, ","},
            {Tokens::NAME, "type"},
            {Tokens::ROUNDED_BRACKET_LEFT, "("},
            {Tokens::NAME, "Product"},
            {Tokens::ROUNDED_BRACKET_RIGHT, ")"},
            {Tokens::ROUNDED_BRACKET_RIGHT, ")"}
    };
    /*
        maker2
        maker
        <
        maker2
        maker
        <-
        maker
        type
        ,
        Product
        pi
        rho
        maker
        type
        ,
        Product
        pi
        U
        sigma
     */
//    std::string input = "σ maker2 < maker ( ρ maker2←maker π maker,type Product U π maker,type Product )";
    ShuntingAlgorithm algorithm;
    algorithm(tokens);
    return 0;
}
