/**
 *  ╒══════════════════════════════════════════════════╕
 *  │                                                  │
 *  │                 RATSQL Project                   │
 *  │            Relational Algebra To SQL             │
 *  │                                                  │
 *  │  Contributors: Pablo Deputter, Cédric Leclercq,  │
 *  │               Robbe Nooyens, Maarten Peirsman    │
 *  │                                                  │
 *  │   University of Antwerp - Advanced Programming   │
 *  │                                                  │
 *  ╘══════════════════════════════════════════════════╛
 */

#include "LevenshteinDistance.h"
#include <thread>
#include <memory>

void LevenshteinDistance::remove(std::string &str, int index) {
    str.erase(index,1);
}

void LevenshteinDistance::replace(std::string &str, int index, const std::string& ch) {
    if (ch.length() > 1)
        return;
    str.replace(index,1,ch);
}

void LevenshteinDistance::add(std::string &str, int index, const std::string& ch) {
    str.insert(index,ch);
}

bool LevenshteinDistance::evalLevenshteinDistance(const std::string &str1, const std::string &str2, int deviation) {

    size_t len1 = str1.size();
    size_t len2 = str2.size();
    // TODO - return what een error :(
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


