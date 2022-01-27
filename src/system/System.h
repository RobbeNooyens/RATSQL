//
// Created by Cédric Leclercq on 26/01/2022.
//

#ifndef RATSQL_PARSING_SYSTEM_H
#define RATSQL_PARSING_SYSTEM_H

#include <string>

#include "../parser/EarleyParser.h"


class System {
public:
    /**
     * @brief Small constructor that creates a new shared pointer to a new earley parser object
     */
    System(): parser() {}
    /**
     * @brief Will parse a relational expression to an SQL statement // todo
     * @param query     Given by reference - will change the string to an SQL statement
     */
    std::string convertToSQL(std::string query);
private:
    /// @brief Shared pointer to an earley parser
    std::shared_ptr<EarleyParser> parser{};
};


#endif //RATSQL_PARSING_SYSTEM_H
