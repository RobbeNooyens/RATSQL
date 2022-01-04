//
// Created by robnoo on 20/12/21.
//

#include <string>
#include <vector>
#include "parser/EarleyParser.h"
#include "parser/ParseTemplate.h"
// #include "parser/Lexer.h"
using namespace std;

int main(int argc, char *argv[]) {
//    vector<ParseToken> tokens{
//        {"number", "1"},
//        {"+", "+"},
//        {"number", "2"},
//        {"*", "*"},
//        {"number", "3"}};
//    std::string cfg = "../input/test2.json";
//    EarleyParser parser(cfg);

    vector<ParseToken> tokens{
            {"PI", "pi"},
            {"NAME", "id"},
            {"ROUNDED_BRACKET_LEFT", "("},
            {"NAME", "Person"},
            {"ROUNDED_BRACKET_RIGHT", ")"}};
    std::string cfg = "../input/grammar.json";
    EarleyParser parser(cfg);

    parser.earleyParse(tokens);

    /*
     * //    vector<string> words{"PI", "NAME", "ROUNDED_BRACKET_LEFT", "NAME", "ROUNDED_BRACKET_RIGHT"};
    vector<ParseToken> words{ParseToken("number", ""), ParseToken("+", ""), ParseToken("number", ""), ParseToken("*", ""), ParseToken("number", "")};
    std::unique_ptr<CFG> g = std::make_unique<CFG>("../input/grammar.json");
    Lexer lexer(g->getAliasMap(), g->getAliases());
    EarleyParser parser(move(g));
    string input = "π a (R)";
    parser.earleyParse(lexer.tokenise(input));
    return 0;
     */
    return 0;
}