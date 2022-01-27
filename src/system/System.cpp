//
// Created by Cédric Leclercq on 26/01/2022.
//

#include "System.h"
#include "../utilities/Parsers.h"
#include "../datastructures/RAExpression.h"

std::string System::convertToSQL(const string& query) {
    lexer = std::make_unique<Lexer>(cfg);
    const auto& tokens = lexer->tokenise(query);
    parser = std::make_unique<EarleyParser>(cfg);
    const auto& tree = parser->earleyParse(tokens);
    return tree->translate();
}
