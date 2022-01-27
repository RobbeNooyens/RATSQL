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

#include <string>
#include "parser/EarleyParser.h"
#include "parser/Lexer.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::shared_ptr<CFG> cfg = make_shared<CFG>("input/grammar.json");
    Lexer lexer = Lexer(cfg->getAliasMap(), cfg->getAliases());
    EarleyParser parser(cfg);
    std::string input = "π  hd σ  model < model2 ( π  model , hd PC ⨝ ρ  model2 ← model π  model , hd PC )";
    auto tokens = lexer.tokenise(input);
    auto tree = parser.earleyParse(tokens);
    auto s = tree->translate();
    return 0;
}