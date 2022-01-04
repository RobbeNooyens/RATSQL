//
// Created by robnoo on 20/12/21.
//

#include <string>
#include <vector>
#include "parser/Parser.h"
#include "parser/ParseToken.h"

using namespace std;

int main(int argc, char *argv[]) {
//    vector<string> words{"PI", "NAME", "ROUNDED_BRACKET_LEFT", "NAME", "ROUNDED_BRACKET_RIGHT"};

//    vector<ParseToken> tokens{
//        {"number", "1"},
//        {"+", "+"},
//        {"number", "2"},
//        {"*", "*"},
//        {"number", "3"}};
//    std::string cfg = "../input/test2.json";
//    Parser parser(cfg);

    vector<ParseToken> tokens{
            {"PI", "pi"},
            {"NAME", "id"},
            {"ROUNDED_BRACKET_LEFT", "("},
            {"NAME", "Person"},
            {"ROUNDED_BRACKET_RIGHT", ")"}};
    std::string cfg = "../input/grammar.json";
    Parser parser(cfg);

    parser.earleyParse(tokens);
    return 0;
}