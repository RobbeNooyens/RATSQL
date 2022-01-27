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

#ifndef RATSQL_UTILS_H
#define RATSQL_UTILS_H

#include <utility>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

namespace Utils {
    /**
     * @brief Convert given string from camel case to snake case
     * @example "RatIsCool" --> "rat_is_cool"
     * @param camel std::string - string in camel case
     * @return std::string in snake case
     */
    static std::string toSnakeCase(const std::string &camel);

    /**
     * @brief Convert given string from snake case to camel case
     * @example "rat_is_cool" --> "RatIsCool"
     * @param snake std::string - string in snake case
     * @return std::string in camel case
     */
    static std::string toCamelCase(const std::string &snake);

    class Matrix {
    private:
        /// The matrix
        std::vector<std::vector<int>> matrix;
    public:
        /**
         * @brief A big constructing boi
         * @param dimX  Dimension X of the matrix (rows)
         * @param dimY  Dimension Y of the matrix (columns)
         */
        Matrix(int dimX, int dimY);

        /**
         * @brief Destructor
         */
        ~Matrix()=default;

        /**
         * @brief Setter for a value in the matrix
         * @param x     Which row in the matrix
         * @param y     Which column in the matrix
         * @param val   Value to put in matrix(x,y)
         */
        void setValue(int x, int y, int val);

        /**
         * @brief Clears the entire matrix
         */
        void clear();

        /**
         * @brief Gets a value out of the matrix of the spot matrix(x,y)
         * @param x     Row of the matrix
         * @param y     Column of the matrix
         * @return
         */
        int getValue(int x, int y) const;

    };

    /**
     * @brief Function to insert an item at a given location in a vector, ensuring there are no duplicates
     * @param v vector to insert into
     * @param iter place to insert in
     * @param t item to insert
     * @return true if item inserted, false if it already existed
     */
    template<typename T>
    bool insert_unique(std::vector<T> &v, typename std::vector<T>::iterator iter, const T &t) {
        if (std::find(v.begin(), v.end(), t) == v.end()) {
            v.insert(iter, t);
            return true;
        }
        return false;
    }

    /**
     * Function to emplace an item in a vector, ensuring there are no duplicates
     * @param v vector to insert into
     * @param t item to insert
     * @return true if item inserted, false if it already existed
     */
    template<typename T>
    bool emplace_back_unique(std::vector<T> &v, const T &t) {
        if (std::find(v.begin(), v.end(), t) == v.end()) {
            v.emplace_back(t);
            return true;
        }
        return false;
    }
}

#endif //RATSQL_UTILS_H
