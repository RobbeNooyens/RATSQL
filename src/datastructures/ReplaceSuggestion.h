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

#ifndef RATSQL_SHUNTING_YARD_REPLACESUGGESTION_H
#define RATSQL_SHUNTING_YARD_REPLACESUGGESTION_H

#include <string>
#include <utility>
#include <vector>

/**
 * ReplaceSuggestion represents a replacement suggestion.
 *
 * The indices vector contains the indices of the words that need to be replaced with the string 'replacement'.
 */
struct ReplaceSuggestion {
    ReplaceSuggestion(std::vector<int> indices, std::string replacement):
    indices(std::move(indices)), replacement(std::move(replacement)) {};
    std::vector<int> indices;
    std::string replacement;
};

#endif //RATSQL_SHUNTING_YARD_REPLACESUGGESTION_H
