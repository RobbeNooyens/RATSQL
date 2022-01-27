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

#ifndef RATSQL_SHUNTING_YARD_RAEXPRESSION_H
#define RATSQL_SHUNTING_YARD_RAEXPRESSION_H

#include <vector>
#include <string>
#include "../parser/ParseTemplate.h"
#include <memory>

class ParseToken;

using RAWord = std::vector<ParseToken>;

class ParseToken;

class RAExpression {
private:
    /// @brief Relation algebra expression
    std::vector<std::shared_ptr<RAWord>> expression;
public:
    /**
     * @brief Default constructor
     */
    RAExpression()=default;
    /**
     * @brief Constructor that will make an expression based on the given vector
     * @param expression    Given vector of strings
     */
    explicit RAExpression(const std::vector<std::string>& expression);
    /**
     * @brief Constructor that will make an expression based on the given vector
     * @param expression    Given vector of strings
     */
    explicit RAExpression(const std::vector<ParseToken>& expression);
    /**
     * @brief Setter for a word in the expression
     * @param index     Index on where the word should come
     */
    void setWord(int index, const std::shared_ptr<RAWord>& word);
    /**
     * @brief Will add a word to the expression
     * @param word      Word to add to the expression
     */
    void addWord(std::shared_ptr<RAWord> &word);
    /**
     * @brief Getter for a word on a given index
     * @param index     Index of the world we want to get
     * @return
     */
    std::shared_ptr<RAWord> getWord(int index);
    /**
     * @brief Getter for the expression
     * @return      Expression
     */
    std::vector<std::shared_ptr<RAWord>> getExpression() const;
    /**
     * @brief Print the expression to a io stream
     * @param stream    io stream to print to
     */
    void printExpression(std::ostream & stream);

    bool operator==(const RAExpression &rhs) const;

};


#endif //RATSQL_SHUNTING_YARD_RAEXPRESSION_H
