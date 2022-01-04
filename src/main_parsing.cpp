//
// Created by robnoo on 20/12/21.
//

#include <string>
#include <vector>
#include "parser/Parser.h"
#include "parser/ParseToken.h"
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

    /*
     * //    vector<string> words{"PI", "NAME", "ROUNDED_BRACKET_LEFT", "NAME", "ROUNDED_BRACKET_RIGHT"};
    vector<TokenTemplate> words{TokenTemplate("number", ""), TokenTemplate("+", ""), TokenTemplate("number", ""), TokenTemplate("*", ""), TokenTemplate("number", "")};
    std::unique_ptr<CFG> g = std::make_unique<CFG>("../input/grammar.json");
    Lexer lexer(g->getAliasMap(), g->getAliases());
    Parser parser(move(g));
    string input = "π a (R)";
    parser.earleyParse(lexer.tokenise(input));
    return 0;
     */
    return 0;
}