//
// Created by Cédric Leclercq on 26/01/2022.
//

#include "System.h"
#include "../datastructures/RAExpression.h"
#include "../algorithms/ShuntingAlgorithm.h"

std::string System::convertToSQL(const string& query) {
    const auto& tokens = lexer->tokenise(query);
    parser = std::make_unique<EarleyParser>(cfg);
    const auto& tree = parser->earleyParse(tokens);
    return tree->translate();
}

std::string System::convertToSQL(const vector<ParseToken>& tokens) {
    parser = std::make_unique<EarleyParser>(cfg);
    const auto& tree = parser->earleyParse(tokens);
    return tree->translate();
}

vector<ParseToken> System::tokenize(string &str) {
    return lexer->tokenise(str);
}

vector<vector<ParseToken>> System::optimize(vector<ParseToken>& tokens) {
    ShuntingAlgorithm shunting;
    shunting(tokens);
    return shunting.getShuntingOutput();
}
