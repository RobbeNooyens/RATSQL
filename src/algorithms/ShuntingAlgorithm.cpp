//
// Created by Cédric Leclercq on 25/11/2021.
//

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
