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
typedef std::pair<std::string, std::vector<std::string>> ProductionRule;
typedef std::set<ProductionRule> ProductionRules;

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

    void print();

private:
    StringSet variables;
    StringSet terminals;
    ProductionRules productionRules;
    std::string startSymbol;

    std::string stringSetToString(StringSet &set);
    std::string stringVectorToString(const std::vector<std::string> &vector);

};


#endif //RATSQL_SHUNTING_YARD_CFG_H
