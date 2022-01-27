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
 * @struct ReplaceSuggestion
 * @brief ReplaceSuggestion represents a replacement suggestion.
 * @note The indices vector contains the indices of the words that need to be replaced with the string 'replacement'.
 */
struct ReplaceSuggestion {
    /**
     * @brief Constructor for replacement suggestion object
     * @param indices       Indices for the member variable indices
     * @param replacement   Replacement for the member variable replacement
     */
    ReplaceSuggestion(std::vector<int> indices, std::string replacement):
    indices(std::move(indices)), replacement(std::move(replacement)) {};
    /// @brief Indices for the struct
    std::vector<int> indices;
    /// @brief Replacements for the struct
    std::string replacement;
};

#endif //RATSQL_SHUNTING_YARD_REPLACESUGGESTION_H
