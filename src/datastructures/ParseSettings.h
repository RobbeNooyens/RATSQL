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

/**
 * @struct Simple struct for the settings of the parser
 */
struct ParseSettings {
    /**
     * @brief Very basic constructor that saves some options for the bool
     * @param autocorrect       Should the parser autocorrect?
     * @param optimizeQuery     Should the parser optimise the query?
     */
    ParseSettings(bool autocorrect, bool optimizeQuery): autocorrect(autocorrect), optimizeQuery(optimizeQuery) {};
    /// @brief Should the parser autocorrect?
    bool autocorrect = false;
    /// @brief Should the parser optimise a query?
    bool optimizeQuery = false;
};


#endif //RATSQL_SHUNTING_YARD_PARSESETTINGS_H
