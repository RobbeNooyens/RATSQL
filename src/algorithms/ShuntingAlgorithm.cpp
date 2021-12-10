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

#include <sstream>
#include <iostream>
#include "ShuntingAlgorithm.h"

using namespace std;

void ShuntingAlgorithm::operator()(string &str) {
    stringstream stream;
    for(char c: str) {
        if(c == ' ') {
            string token = stream.str();
            parser.consume(token);
            stream.str(string());
        } else {
            stream << c;
        }
    }
    if(!stream.str().empty()) {
        string token = stream.str();
        parser.consume(token);
    }
    parser.flush();
    parser.printOperatorStack();
    parser.printQueue();
    parser.generateOutput(cout);
}
