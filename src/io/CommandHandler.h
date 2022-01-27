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

#ifndef RATSQL_SHUNTING_YARD_COMMANDHANDLER_H
#define RATSQL_SHUNTING_YARD_COMMANDHANDLER_H


#include <string>
#include <memory>

class RAExpression;

/**
 * @class CommandHandler
 * @brief Class for handling the commands of the cmd functionality
 */
class CommandHandler {
public:
    /**
     * @brief Operator overload to handle a command
     * @param command   command to handle
     */
    void operator()(std::string& command);
private:
    /// @brief Relational algebra expression
    std::shared_ptr<RAExpression> expression;
    /// @brief The name of the current command
    std::string commandName;
    /// @brief The arguments of the current command
    std::vector<std::string> arguments;
    /**
     * @brief Function to call for levenshtein distance command
     */
    void levDisCmd();
    /**
     * @brief Function to call to "check typos" command
     */
    void checkTypos();
    /**
     * @brief Function to call to "auto correct" the input command
     */
    void autocorrect();
    /**
     * @brief Function to call to load a relational algebra expression
     */
    void loadRA();
    /**
     * @brief Function to call to check if the conventions are respected
     */
    void checkConventions();
    /**
     * @brief Function to call to automatically check the coding conventions
     */
    void autoConventions();
    /**
     * @brief Function to change a relational algebra expression to a SQL statement
     */
    void toSQL();
    /**
     * @brief Static function to parse an input
     */
    static void parse();
};


#endif //RATSQL_SHUNTING_YARD_COMMANDHANDLER_H
