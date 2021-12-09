//
// Created by robnoo on 10/12/21.
//

#include "Parsers.h"

// Include datastructures
#include "../datastructures/ParseSettings.h"
#include "../datastructures/RAExpression.h"
#include "../datastructures/ReplaceSuggestion.h"
#include "../datastructures/SQLStatement.h"

std::vector<ReplaceSuggestion> parsers::checkTypos(const std::shared_ptr<RAExpression> &expression) {
    return {};
}

void parsers::autocorrect(std::shared_ptr<RAExpression> &expression) {

}

void parsers::optimizeRA(std::shared_ptr<RAExpression> &expression) {

}

std::shared_ptr<SQLStatement>
parsers::toSQL(const std::shared_ptr<RAExpression> &expression, ParseSettings &settings) {
    return {};
}
