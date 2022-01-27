//
// Created by robnoo on 20/12/21.
//

#include <string>
#include <vector>
#include <iostream>
#include "parser/EarleyParser.h"
#include "parser/ParseTemplate.h"
#include "parser/Lexer.h"
#include "utilities/Utils.h"

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

/// Optie 1 -> zonder lexer

//    std::string grammar = "../input/grammar.json";
//    EarleyParser parser(grammar);
//    vector<ParseToken> tokens{
//            {"PI", "pi"},
//            {"NAME", "id"},
//            {"ROUNDED_BRACKET_LEFT", "("},
//            {"NAME", "Person"},
//            {"ROUNDED_BRACKET_RIGHT", ")"}};

/// Optie 2 -> met lexer

    std::vector<std::string> v = {"a", "b"};
    std::string a = "a";
    auto b = Utils::insert_unique(v, v.begin(), a);

    std::shared_ptr<CFG> cfg = make_shared<CFG>("input/grammar.json");
    Lexer lexer = Lexer(cfg->getAliasMap(), cfg->getAliases());
    EarleyParser parser(cfg);
//    std::string input = "σ model = 1001 pi maker, model sigma type = 'pc' pi maker, model, type (Product)";
//    std::string input = "sigma model = 1001 pi maker, model sigma type = 'pc' pi maker, model, type (Product)";
//    std::string input = "sigma name = 'a' pi name sigma id = 1 pi id, name (test)";
//    std::string input = "Product ⨝ model < 1010 (rho model→m (PC)) ⨝ Laptop";
//    std::string input = "PC ∪ pi model, speed, ram, hd, price Laptop";
    std::string input = "pi model (PC intersect pi model, speed, ram, hd, price Laptop)";
//    std::string input = "pi model, maker pi model, maker, type (Product)";
//    std::string input = "sigma m <= 1010 rho model→m rho K sigma type = 'laptop' pi model, price, type sigma price <= 1000 (PC)";
    auto tokens = lexer.tokenise(input); // Todo: error voor lege string / vermijden dat er geconvert kan worden in (ook spaties tellen niet)
    for (auto &t : tokens) {
        std::cout << t << "\t";
    }
    auto tree = parser.earleyParse(tokens);
    auto s = tree->translate();

    std::cout << std::endl << s << std::endl;
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