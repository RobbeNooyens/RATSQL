//
// Created by Cédric Leclercq on 25/11/2021.
//

#include "LevenshteinDistance.h"
#include <thread>

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

    std::shared_ptr<Utils::Matrix> m = std::make_shared<Utils::Matrix>(len1 + 1, len2 + 1);

    for (int i = 0; i <= (int) len1; i++) {
        m->setValue()
    }

    for (int i = 0; i <= (int) len2; i++) {
    }


    return false;
}


