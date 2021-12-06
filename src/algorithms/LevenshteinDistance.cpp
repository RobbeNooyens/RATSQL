//
// Created by Cédric Leclercq on 25/11/2021.
//

#include "LevenshteinDistance.h"

__attribute__((unused)) void LevenshteinDistance::remove(std::string &str, int index) {
    str.erase(index,1);
}

__attribute__((unused)) void LevenshteinDistance::replace(std::string &str, int index, const std::string& ch) {
    if (ch.length() > 1)
        return;
    str.replace(index,1,ch);
}

__attribute__((unused)) void LevenshteinDistance::add(std::string &str, int index, const std::string& ch) {
    str.insert(index,ch);
}

bool LevenshteinDistance::evalLevenshteinDistance(const std::string &str1, const std::string &str2, int deviation) {

    // Get size of strings
    int len1 = (int) str1.size();
    int len2 = (int) str2.size();

    if (len1 == 0 || len2 == 0) return false;

    // Create matrix
    std::shared_ptr<Utils::Matrix> m = std::make_shared<Utils::Matrix>(len1 + 1, len2 + 1);

    // Initialize the matrix
    for (int i = 0; i <= len1; i++) m->setValue(i, 0, i);
    for (int i = 0; i <= len2; i++) m->setValue(0, i, i);

    // Fill matrix
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {

            // If characters are equal, added cost is 1
            int equalFlag = 0;
            if (str1[i - 1] != str2[j - 1]) equalFlag = 1;

            // Get minimum
            int min = std::min(m->getValue(i - 1, j) + 1,
                               std::min(m->getValue(i, j - 1) + 1,
                               m->getValue(i - 1, j - 1) + equalFlag));
            // Set value of calculated cost
            m->setValue(i, j, min);
        }
    }
    // If cost is <= deviation, return true
    return m->getValue(len1,len2) <= deviation;
}


