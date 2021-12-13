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

#ifndef RATSQL_SHUNTING_YARD_PARSESETTINGS_H
#define RATSQL_SHUNTING_YARD_PARSESETTINGS_H


struct ParseSettings {
    ParseSettings(bool autocorrect, bool optimizeQuery): autocorrect(autocorrect), optimizeQuery(optimizeQuery) {};
    bool autocorrect = false;
    bool optimizeQuery = false;
};


#endif //RATSQL_SHUNTING_YARD_PARSESETTINGS_H
