//
// Created by Cédric Leclercq on 26/01/2022.
//

#ifndef RATSQL_PARSING_SYSTEM_H
#define RATSQL_PARSING_SYSTEM_H

#include <string>

#include "../parser/EarleyParser.h"
#include "../parser/Lexer.h"


class System {
public:
    /**
     * @brief Small constructor that creates a new shared pointer to a new earley parser object
     */
    System(): parser(), lexer() {
        cfg = std::make_shared<CFG>("input/grammar.json");
        lexer = std::make_unique<Lexer>(cfg);
    }
    /**
     * @brief Will parse a relational expression to an SQL statement // todo
     * @param query     Given by reference - will change the string to an SQL statement
     */
    std::string convertToSQL(const std::string& query);

    vector<ParseToken> tokenize(std::string& str);

    vector<vector<ParseToken>> optimize(vector<ParseToken>& tokens);

private:
    /// @brief Shared pointer to an earley parser
    std::unique_ptr<EarleyParser> parser{};
    std::unique_ptr<Lexer> lexer{};
    std::shared_ptr<CFG> cfg{};
};


#endif //RATSQL_PARSING_SYSTEM_H
