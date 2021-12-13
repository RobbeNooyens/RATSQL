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

#ifndef RATSQL_SHUNTING_YARD_GUIHANDLER_H
#define RATSQL_SHUNTING_YARD_GUIHANDLER_H

#include <memory>
#include <vector>

class RAExpression;
class SQLStatement;

class GUIHandler {
public:
    // TODO: implement class

private:
    std::shared_ptr<RAExpression> ra;
    std::shared_ptr<SQLStatement> sql;
};


#endif //RATSQL_SHUNTING_YARD_GUIHANDLER_H
