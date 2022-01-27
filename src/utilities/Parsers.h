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

#ifndef RATSQL_SHUNTING_YARD_PARSERS_H
#define RATSQL_SHUNTING_YARD_PARSERS_H

#include <memory>
#include <vector>

class ReplaceSuggestion;
class RAExpression;
class SQLStatement;
class ParseSettings;

/**
 * @namespace
 * @designPattern Adapt pattern
 */
namespace parsers {
    // Error correction
    std::vector<ReplaceSuggestion> checkTypos(const std::shared_ptr<RAExpression>& expression);

    // Optimization
    std::shared_ptr<RAExpression> optimizeRA(const std::shared_ptr<RAExpression>& expression);

    // Naming conventions
    std::vector<ReplaceSuggestion> checkNamingConventions(const std::shared_ptr<RAExpression>& expression);

    // SQL parser
    std::shared_ptr<SQLStatement> toSQL(const std::shared_ptr<RAExpression>& expression, ParseSettings& settings);

};

#endif //RATSQL_SHUNTING_YARD_PARSERS_H
