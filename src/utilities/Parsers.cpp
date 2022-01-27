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

#include "Parsers.h"
#include "../datastructures/ParseSettings.h"
#include "../datastructures/RAExpression.h"
#include "../datastructures/ReplaceSuggestion.h"
#include "../datastructures/SQLStatement.h"


std::vector<ReplaceSuggestion> parsers::checkTypos(const std::shared_ptr<RAExpression> &expression) {
    // TODO implement
    return {};
}

std::shared_ptr<RAExpression> parsers::optimizeRA(const std::shared_ptr<RAExpression> &expression) {
    // TODO implement
    return {};
}

std::shared_ptr<SQLStatement>
parsers::toSQL(const std::shared_ptr<RAExpression> &expression, ParseSettings &settings) {
    // TODO implement
    return {};
}

std::vector<ReplaceSuggestion> parsers::checkNamingConventions(const std::shared_ptr<RAExpression> &expression) {
    // TODO implement
    return {};
}

std::shared_ptr<RAExpression> parsers::toRelationalExpression(const string &query) {
    // Aight ouders van kiddos zijn hier, ik zen em, morgen is men stuk af
    return std::shared_ptr<RAExpression>();
}
