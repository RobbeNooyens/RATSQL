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

#include "LevenshteinDistance.h"
#include "../exceptions/ExceptionHandler.h"
#include <thread>
#include <memory>

bool LevenshteinDistance::evalLevenshteinDistance(const std::string &str1, const std::string &str2, int deviation) {

    size_t len1 = str1.size();
    size_t len2 = str2.size();
    if (len1 == 0 || len2 == 0) return false;

    // Create matrix
    std::shared_ptr<Utils::Matrix> m = std::make_shared<Utils::Matrix>(len1 + 1, len2 + 1);

    // Initialize the matrix
    for (int i = 0; i <= len1; i++) m->setValue(i, 0, i);
    for (int i = 0; i <= len2; i++) m->setValue(0, i, i);

    // Fill matrix
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {

            int equalFlag = 0;
            if (str1[i - 1] != str2[j - 1]) equalFlag = 1;

            int min = std::min(m->getValue(i - 1, j) + 1,
                               std::min(m->getValue(i, j - 1) + 1,
                               m->getValue(i - 1, j - 1) + equalFlag));
            m->setValue(i, j, min);
        }
    }
    return m->getValue((int)len1,(int)len2) <= deviation;
}

LevenshteinDistance::LevenshteinDistance(const std::string& path) {
    std::ifstream file(path);
    try {
        std::string str;
        while (std::getline(file, str)) { mDict.emplace_back(str); }
        file.close();
    } catch (std::exception& e) {
        ExceptionHandler::handle(e,"Levenshtein distance file path not found!");
    }
}

LevenshteinDistance &LevenshteinDistance::getInstance() {
    static LevenshteinDistance instance("resources/words_small.txt");
    return instance;
}

std::pair<bool, std::vector<std::string>> LevenshteinDistance::eval(const std::string &str1, int deviation, bool skip) {
    std::vector<std::string> sugg;
    bool flag = false;
    for (const auto &i : mDict) {
        if (str1 == i) {
            flag = true;
            if (skip) { return {flag, sugg}; }
        }

        if (evalLevenshteinDistance(str1, i, deviation)) {
            sugg.emplace_back(i);
        }
    }
    return {flag,sugg};
}

