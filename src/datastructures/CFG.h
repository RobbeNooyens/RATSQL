//
// Created by robnoo on 20/12/21.
//

#ifndef RATSQL_SHUNTING_YARD_CFG_H
#define RATSQL_SHUNTING_YARD_CFG_H

#include <set>
#include <string>
#include <map>
#include <vector>

typedef std::set<std::string> StringSet;
typedef std::pair<std::string, std::vector<std::string>> Production;
typedef std::set<Production> ProductionRules;

class CFG {
public:
    CFG();
    CFG(StringSet  variables, StringSet  terminals, ProductionRules  productionRules, std::string  startSymbol);
    CFG(const std::string& json);
    StringSet getVariables();
    StringSet getTerminals();
    ProductionRules getProductionRules();
    std::string getStartSymbol();
    bool accepts(const std::string&);
    bool isVariable(const std::string& s);
    bool isTerminal(const std::string& s);
    ProductionRules getRules(const std::string& head);

    const std::vector<std::vector<std::string>> &getAliases() const;

    const std::map<std::string, std::string> &getAliasMap() const;

    void print();

private:
    StringSet variables;
    StringSet terminals;
    ProductionRules productionRules;
    std::string startSymbol;

    std::vector<std::vector<std::string>> aliases;

    std::map<std::string, std::string> aliasMap;

    std::string stringSetToString(StringSet &set);
    std::string stringVectorToString(std::vector<std::string> &vector);

};


#endif //RATSQL_SHUNTING_YARD_CFG_H
