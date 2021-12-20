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

#include <sstream>
#include <iostream>
#include "ShuntingAlgorithm.h"

using namespace std;

void ShuntingAlgorithm::operator()(string &str, std::ostream& stream) {
    stringstream strStream;
    for(char c: str) {
        if(c == ' ') {
            string token = strStream.str();
            parser.consume(token);
            strStream.str(string());
        } else {
            strStream << c;
        }
    }
    if(!strStream.str().empty()) {
        string token = strStream.str();
        parser.consume(token);
    }
    parser.flush();
    parser.printOperatorStack();
    parser.printQueue();
    parser.generateOutput(stream);
}

ShuntingYardParser ShuntingAlgorithm::getParser() const {
    return this->parser;
}
