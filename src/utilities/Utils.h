//
// Created by Cédric Leclercq on 29/11/2021.
//

#ifndef RATSQL_UTILS_H
#define RATSQL_UTILS_H

#include <utility>
#include <vector>
#include <string>

namespace Utils {

    class Matrix {
    private:
        /// The matrix
        std::vector<std::vector<int>> matrix;
    public:
        /**
         * A big constructing boi
         * @param dimX  Dimension X of the matrix (rows)
         * @param dimY  Dimension Y of the matrix (columns)
         */
        Matrix(int dimX, int dimY) {
            this->matrix = std::vector<std::vector<int>>(dimX, std::vector<int>(dimY));
        }
        /**
         * Setter for a value in the matrix
         * @param x     Which row in the matrix
         * @param y     Which column in the matrix
         * @param val   Value to put in matrix(x,y)
         */
        void setValue(int x, int y, int val) {
            assert(x < this->matrix.size());
            assert(y < this->matrix[x].size());
            this->matrix[x][y] = val;
        }
        /**
         * Clears the entire matrix
         */
        void clear() {
            for (auto item: this->matrix) {
                item.clear();
            }
            this->matrix.clear();
        }
        /**
         * Gets a value out of the matrix of the spot matrix(x,y)
         * @param x     Row of the matrix
         * @param y     Column of the matrix
         * @return
         */
        int getValue(int x, int y) const {
            assert(x < this->matrix.size());
            assert(y < this->matrix[x].size());
            return this->matrix[x][y];
        }

    };
}

#endif //RATSQL_UTILS_H
