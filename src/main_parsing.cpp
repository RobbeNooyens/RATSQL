//
// Created by robnoo on 20/12/21.
//

#include <string>
#include <vector>
#include "parser/Parser.h"

using namespace std;

int main(int argc, char *argv[]) {
//    vector<string> words{"PI", "NAME", "ROUNDED_BRACKET_LEFT", "NAME", "ROUNDED_BRACKET_RIGHT"};
    vector<string> words{"number", "+", "number", "*", "number"};
    Parser parser;
    parser.earleyParse(words);
    return 0;
}