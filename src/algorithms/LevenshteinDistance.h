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

    LevenshteinDistance(std::string path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            // TODO - error
        }
        std::string str;
        while (std::getline(file, str)) {  mDict.emplace_back(str); }
        file.close();
    }
public:
    LevenshteinDistance& operator=(const LevenshteinDistance&) = delete;

    LevenshteinDistance(const LevenshteinDistance&) = delete;

    static LevenshteinDistance& getInstance()
    {
        static LevenshteinDistance instance("resources/words_small.txt");
        return instance;
    }

    std::pair<bool, std::vector<const std::string>> eval(const std::string& str1, int deviation = 2)
    {
        std::vector<const std::string> sugg;
        std::cout << str1 << "\n";
        bool flag = false;
        for (const auto &i : mDict)
        {
            if (evalLevenshteinDistance(str1, i, deviation)) { sugg.emplace_back(i); }
            if (str1 == i) { flag = true; }
        }
        return {flag,sugg};
    }

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
