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

#ifndef RATSQL_SHUNTING_YARD_COMMANDHANDLER_H
#define RATSQL_SHUNTING_YARD_COMMANDHANDLER_H


#include <string>
#include <memory>

class RAExpression;

class CommandHandler {
public:
    void operator()(std::string& command);

private:
    std::shared_ptr<RAExpression> expression;

    std::string commandName;
    std::vector<std::string> arguments;

    void levDisCmd();
    void checkTypos();
    void autocorrect();
    void loadRA();
    void checkConventions();
    void autoConventions();
    void toSQL();
};


#endif //RATSQL_SHUNTING_YARD_COMMANDHANDLER_H
