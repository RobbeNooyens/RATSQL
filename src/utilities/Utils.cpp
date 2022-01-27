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

#include "Utils.h"

using namespace Utils;


std::string toSnakeCase(const std::string &camel) {
    std::string snake = std::string(1, std::tolower(camel[0]));

    auto it = std::begin(camel) + 1;
    while (it != std::end(camel)) {
        if (std::isupper(*it))
        {
            const auto& c = *(it - 1);
            if (c != '_' && std::islower(c)) { snake += "_"; }
        }
        snake += std::tolower(*it);
        it++;
    }
    return snake;
}

std::string toCamelCase(const std::string &snake) {
    std::string camel = std::string(1, std::toupper(snake[0]));

    auto it = std::begin(snake) + 1;
    while (it != std::end(snake))
    {
        const auto& c = (*it);
        if (c == '_')
        {
            camel += std::toupper(*(it + 1));
            it += 2;
            continue;
        }
        camel += c;
        it++;
    }
    return camel;
}

Matrix::Matrix(int dimX, int dimY) {
    this->matrix = std::vector<std::vector<int>>(dimX, std::vector<int>(dimY));
}

void Matrix::setValue(int x, int y, int val) {
    assert(x < this->matrix.size());
    assert(y < this->matrix[x].size());
    this->matrix[x][y] = val;
}

int Matrix::getValue(int x, int y) const {
    assert(x < this->matrix.size());
    assert(y < this->matrix[x].size());
    return this->matrix[x][y];
}

void Matrix::clear() {
    for (auto item: this->matrix) {
        item.clear();
    }
    this->matrix.clear();
}
