//
// Created by robnoo on 20/12/21.
//

#include <string>
#include <vector>
#include "parser/Parser.h"
#include "parser/Lexer.h"

using namespace std;

int main(int argc, char *argv[]) {
//    vector<string> words{"PI", "NAME", "ROUNDED_BRACKET_LEFT", "NAME", "ROUNDED_BRACKET_RIGHT"};
    vector<TokenTemplate> words{TokenTemplate("number", ""), TokenTemplate("+", ""), TokenTemplate("number", ""), TokenTemplate("*", ""), TokenTemplate("number", "")};
    std::unique_ptr<CFG> g = std::make_unique<CFG>("../input/grammar.json");
    Lexer lexer(g->getAliasMap(), g->getAliases());
    Parser parser(move(g));
    string input = "π a (R)";
    wstring k(input.begin(), input.end());
    parser.earleyParse(lexer.tokenise(k));
    return 0;
}