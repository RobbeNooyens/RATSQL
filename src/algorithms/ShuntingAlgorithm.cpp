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
            SAParser.consume(token);
            strStream.str(string());
        } else {
            strStream << c;
        }
    }
    if(!strStream.str().empty()) {
        string token = strStream.str();
        SAParser.consume(token);
    }
    SAParser.flush();
    SAParser.parse(stream);
}

ShuntingYardParser ShuntingAlgorithm::getParser() const {
    return this->SAParser;
}
