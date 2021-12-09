//
// Created by robnoo on 9/12/21.
//

#ifndef RATSQL_SHUNTING_YARD_PARSERS_H
#define RATSQL_SHUNTING_YARD_PARSERS_H

#include <memory>
#include <vector>

class ReplaceSuggestion;
class RAExpression;
class SQLStatement;
class ParseSettings;


namespace parsers {
    std::vector<ReplaceSuggestion> checkTypos(const std::shared_ptr<RAExpression>& expression);
    void autocorrect(std::shared_ptr<RAExpression>& expression);
    void optimizeRA(std::shared_ptr<RAExpression>& expression);
    std::shared_ptr<SQLStatement> toSQL(const std::shared_ptr<RAExpression>& expression, ParseSettings& settings);
};

#endif //RATSQL_SHUNTING_YARD_PARSERS_H
