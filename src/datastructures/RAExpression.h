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

class RAExpression {
private:
    /// @brief Relation algebra expression
    std::vector<std::string> expression;
public:
    /**
     * @brief Default constructor
     */
    RAExpression()=default;
    /**
     * @brief Constructor that will make an expression based on the given vector
     * @param expression    Given vector of strings
     */
    explicit RAExpression(std::vector<std::string> expression);
    /**
     * @brief Setter for a word in the expression
     * @param index     Index on where the word should come
     */
    void setWord(int index, const std::string& word);
    /**
     * @brief Getter for a word on a given index
     * @param index     Index of the world we want to get
     * @return
     */
    std::string getWord(int index);
    /**
     * @brief Getter for the expression
     * @return      Expression
     */
    std::vector<std::string> getExpression() const;
    /**
     * @brief Print the expression to a io stream
     * @param stream    io stream to print to
     */
    void printExpression(std::ostream & stream);

};


#endif //RATSQL_SHUNTING_YARD_RAEXPRESSION_H
