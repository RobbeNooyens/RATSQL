//
// Created by Cédric Leclercq on 25/11/2021.
//

#ifndef RATSQL_LEVENSHTEINDISTANCE_H
#define RATSQL_LEVENSHTEINDISTANCE_H

#include <string>

#include "../utilities/Utils.h"

class LevenshteinDistance {
private:
    /**
     *
     * @param str
     * @param index
     */
    __attribute__((unused)) static void remove(std::string& str, int index);
    /**
     *
     * @param str
     * @param index
     * @param ch
     */
    __attribute__((unused)) static void replace(std::string& str, int index, const std::string& ch);
    /**
     *
     * @param str
     * @param index
     * @param ch
     */
    __attribute__((unused)) static void add(std::string& str, int index, const std::string& ch);
public:
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
