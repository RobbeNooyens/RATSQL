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

#ifndef RATSQL_LEVENSHTEINDISTANCE_H
#define RATSQL_LEVENSHTEINDISTANCE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "../utilities/Utils.h"

class LevenshteinDistance {
private:
    std::vector<std::string> mDict;

    explicit LevenshteinDistance(const std::string& path);
public:
    LevenshteinDistance& operator=(const LevenshteinDistance&) = delete;

    LevenshteinDistance(const LevenshteinDistance&) = delete;

    LevenshteinDistance& operator=(const LevenshteinDistance&&) = delete;

    LevenshteinDistance(const LevenshteinDistance&&) = delete;

    static LevenshteinDistance& getInstance();

    /**
     * @brief Evaluates a string compared with the dictionary
     * @param str1      input string
     * @param deviation max allowed levenshtein deviation
     * @param skip return if one match is found
     * @return  pair(wordFoundInDictionary, similarWordsToInput)
     */
    std::pair<bool, std::vector<std::string>> eval(const std::string& str1, int deviation = 2, bool skip = false);

    /**
     * Function that evaluates the levenshtein distance according to a deviation.
     * If the levenshtein distance between the first string and the second string <= deviation, then true.
     * This function will be used for automatic correcting of typos when parsing ReLaX code.
     * @param str1          First string used for calculating
     * @param str2          Second string used for calculating
     * @param deviation     Max deviation allowed
     * @return              LevenshteinDistance::levenshteinDistance(str1,str2) <= deviation
     */
    static bool evalLevenshteinDistance(const std::string& str1, const std::string& str2, int deviation=2);
};


#endif //RATSQL_LEVENSHTEINDISTANCE_H
