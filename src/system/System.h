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
    System(): parser() {
        cfg = std::make_shared<CFG>("input/grammar.json");
        lexer = std::make_unique<Lexer>(cfg);
    }
    /**
     * @brief Will parse a relational expression to an SQL statement // todo
     * @param query     Given by reference - will change the string to an SQL statement
     */
    std::string convertToSQL(const std::string& query);
    /**
     * @brief Tokenize a given std::string
     * @param str std::string - given string
     * @return vector<ParseToken> - tokens
     */
    vector<ParseToken> tokenize(std::string& str);
    /**
     * @brief Optimize a given expression in vector of ParseToken forms
     * @param tokens std::vector<ParseToken> - tokens to be optimized by reference
     * @return vector<vector<ParseToken>> - optimized tokens
     */
    vector<vector<ParseToken>> optimize(vector<ParseToken>& tokens);
    /**
     * @brief Convert given query to SQL form
     * @param query std::vector<ParseToken> - query to be converted to SQL
     * @return std::string - converted query in SQL form
     */
    string convertToSQL(const vector<ParseToken> &query);
private:
    /// @brief Unique pointer to an earley parser
    std::unique_ptr<EarleyParser> parser{};
    /// @brief Unique pointer to
    std::unique_ptr<Lexer> lexer{};
    /// @brief Shared pointer to CFG
    std::shared_ptr<CFG> cfg{};
};

#endif //RATSQL_PARSING_SYSTEM_H
