/**
 *@brief Get aliases (=aliases for terminals/variables of grammar)
 * @return std::vector<std::vector<std::string>> - aliases by reference
 */

#ifndef RATSQL_SHUNTING_YARD_CFG_H
#define RATSQL_SHUNTING_YARD_CFG_H

#include <set>
#include <string>
#include <map>
#include <vector>

typedef std::set<std::string> StringSet;
typedef std::pair<std::string, std::vector<std::string>> ProductionRule;
typedef std::set<ProductionRule> ProductionRules;

/**
 * @class CFG
 * @brief Class implemented for Context-Free-Grammar
 */
class CFG {
public:
    /**
     * @brief Default constructor for CFG object
     */
    CFG();
    /**
     * @brief Constructor for CFG object
     * @param variables std::set -  contains variables of grammar
     * @param terminals std::set -  contains terminals of grammar
     * @param productionRules std::set -  contains rules
     * @param startSymbol std::string - symbol of start variable
     */
    CFG(StringSet  variables, StringSet  terminals, ProductionRules  productionRules, std::string  startSymbol);
    /**
     * @brief Construct for CFG object from json file
     * @param json std::string - path to json file
     */
    explicit CFG(const std::string& json);
    /**
     * @brief Get variables
     * @return std::set - variables
     */
    StringSet getVariables();
    /**
     * @brief Get terminals
     * @return std::set - terminals
     */
    StringSet getTerminals();
    /**
     * @brief Get production rules
     * @return std::set - production rules
     */
    ProductionRules getProductionRules();
    /**
     * @brief Get start symbol
     * @return std::string - start symbol
     */
    std::string getStartSymbol();
    /**
     * @brief Check if given std::string is accepted by grammar using the CYK-algorithm
     * @return bool - true if accepted
     */
    bool accepts(const std::string&);
    /**
     * @brief Check if given std::string is a variable
     * @param bool - true if std::string is a variable
     * @return bool - true if given std::string is a variable
     */
    bool isVariable(const std::string& s);
    /**
     * @brief Check if given std::string is a terminal
     * @param bool - true if std::string is a terminal
     * @return bool - true if given std::string is a terminal
     */
    bool isTerminal(const std::string& s);
    /**
     * @brief Get production rules for a given variable
     * @return std::set - production rules
     */
    ProductionRules getRules(const std::string& head);
    /**
     *@brief Get aliases (=aliases for terminals/variables of grammar)
     * @return std::vector<std::vector<std::string>> - aliases by reference
     */    /**
     *@brief Get aliases (=aliases for terminals/variables of grammar)
     * @return std::vector<std::vector<std::string>> - aliases by reference
     */
    const std::vector<std::vector<std::string>> &getAliases() const;
    /**
     *@brief Get aliases as a map (=aliases for terminals/variables of grammar)
     * @return std::map<std::string, std::string>> - aliases as map by reference
     */
    const std::map<std::string, std::string> &getAliasMap() const;
    /**
     * @brief Print the CFG info: variables, terminals, startsymbol and productionrules
     */
    void print();
private:
    /// StringSet - Variables of the grammar
    StringSet variables;
    /// StringSet - Terminals the grammar
    StringSet terminals;
    /// ProductionRules - Rules of the grammar
    ProductionRules productionRules;
    /// std::string - Start symbol of the grammar, needs to be a variable
    std::string startSymbol;
    /// std::vector<std::vector<std::string>> - Aliases of the grammar terminals and variables
    std::vector<std::vector<std::string>> aliases;
    /// std::vector<std::vector<std::string>> - Aliases of the grammar terminals and variables as a map
    std::map<std::string, std::string> aliasMap;

    /**
     * @brief Convert a StringSet to std::string
     * @param set StringSet - set
     * @return std::string - string
     */
    std::string stringSetToString(StringSet &set);
    /**
     * @brief Convert std::vector containing std::string to a std::string
     * @param vector std::vector<std::string> - vector containing strings
     * @return std::string - string
     */
    std::string stringVectorToString(const std::vector<std::string> &vector);
};

#endif //RATSQL_SHUNTING_YARD_CFG_H
