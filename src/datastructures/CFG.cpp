//
// Created by robnoo on 20/12/21.
//

#include "CFG.h"
#include "../../libs/json.hpp"
#include <iostream>
#include <fstream>
#include <utility>
#include <string>

using namespace std;
using json = nlohmann::json;
using TableEntry = set<string>;
using Row = vector<TableEntry>;
using Table = vector<Row>;

struct CYK {
    CFG* cfg;
    Table table;
    TableEntry* currentEntry;
    int r,c;
    int tableSize;
    CYK(CFG* cfg): cfg(cfg){}
    void operator()(string str) {
        tableSize = (int) str.length();
        table.clear();
        Row emptyRow;
        for(int j = 0; j < tableSize; j++) {
            emptyRow.push_back(TableEntry());
        }
        for(int i = 0; i < tableSize; i++) {
            table.push_back(emptyRow);
        }
        // [ ] [ ] [ ]
        // [ ] [ ]
        // [ ]
        for(r = 0; r < table.size(); r++) {
            Row* row = &table[r];
            for(c = 0; c < row->size()-r; c++) {
                currentEntry = &(row->at(c));
                vector<string> combinations;
                if(r == 0) {
                    combinations.push_back({str[c]});
                } else {
                    generateStateCombinations(combinations);
                }
                for(const auto& vars: combinations) {
                    fillCurrentEntry(vars);
                }
            }
        }
    }
    void generateStateCombinations(vector<string>& combinations) {
        for(int i = 0; i < r; i++) {
            TableEntry e1 = table[i][c];
            TableEntry e2 = table[r-i-1][c+i+1];
            for(const auto& state1: e1){
                for(const auto& state2: e2) {
                    combinations.push_back(state1 + state2);
                }
            }

        }
    }
    void fillCurrentEntry(const string& vars) {
        for(const auto& production: cfg->getProductionRules()) {
            string replacementString;
            for(const auto& replacement: production.second) {
                replacementString.append(replacement);
            }
            if(replacementString == vars) {
                currentEntry->insert(production.first);
            }
        }
    }
    bool accepts() {
        string startSymbol = cfg->getStartSymbol();
        for(const auto& symbol: table[tableSize-1][0]) {
            if(symbol == startSymbol)
                return true;
        }
        return false;
    }
    void print() {
        vector<int> charsPerColumn{tableSize};
        for(int i = 0; i < tableSize; i++)
            charsPerColumn.push_back(0);
        for(const auto& row: table) {
            for(int i = 0; i < row.size(); i++) {
                int chars = 2*((int)row[i].size()-1);
                for(const auto& entry: row[i]) {
                    chars += (int) entry.length();
                }
                if(charsPerColumn[i] < chars) {
                    charsPerColumn[i] = chars;
                }
            }
        }
        for(int i = tableSize-1; i >= 0; i--) {
            Row row = table[i];
            cout << "|";
            for(int j = 0; j < row.size()-i; j++) {
                printEntry(row[j], charsPerColumn[j]);
                cout << "|";
            }
            cout << endl;
        }
    }
    void printEntry(const TableEntry& entry, int size) {
        int charCount = 0;
        cout << " {";
        int i = 0;
        for(const auto& variable: entry) {
            charCount += (int) variable.size();
            cout << variable;
            if(i < entry.size()-1) {
                cout << ", ";
                charCount += 2;
            }
            i++;
        }
        cout << "}  ";
        for(int i = 0; i < size - charCount; i++) {
            cout << " ";
        }
    }

};

CFG::CFG() {
    this->variables = {"BINDIGIT", "S"};
    this->terminals = {"0", "1", "a", "b"};
    this->productionRules = {
            {"BINDIGIT", {"0"}},
            {"BINDIGIT", {"1"}},
            {"S", {""}},
            {"S", {"a", "S", "b", "BINDIGIT"}} };
    this->startSymbol = "S";

}

StringSet CFG::getVariables() {
    return this->variables;
}

StringSet CFG::getTerminals() {
    return this->terminals;
}

ProductionRules CFG::getProductionRules() {
    return this->productionRules;
}

std::string CFG::getStartSymbol() {
    return this->startSymbol;
}

void CFG::print() {
    std::cout << "V = {" << stringSetToString(this->variables) << "}" << std::endl;
    std::cout << "T = {" << stringSetToString(this->terminals) << "}" << std::endl;
    std::cout << "P = {" << std::endl;
    for(Production production: productionRules) {
        std::cout << "    " << production.first << "   -> `" << stringVectorToString(production.second) << "`" << std::endl;
    }
    std::cout << "}" << std::endl;
    std::cout << "S = " << startSymbol << std::endl;
}

std::string CFG::stringSetToString(StringSet &set) {
    std::string output;
    int count = 0;
    for(const std::basic_string<char>& s: set) {
        output.append(s);
        if(count < set.size()-1)
            output.append(", ");
        count++;
    }
    return output;
}

std::string CFG::stringVectorToString(std::vector<std::string> &vector) {
    std::string output;
    int count = 0;
    for(const std::basic_string<char>& s: vector) {
        output.append(s);
        if(count < vector.size()-1)
            output.push_back(' ');
        count++;
    }
    return output;
}

CFG::CFG(StringSet  variables, StringSet  terminals, ProductionRules  productionRules, std::string  startSymbol): variables(std::move(variables)), terminals(std::move(terminals)), productionRules(std::move(productionRules)), startSymbol(std::move(startSymbol)) {

}

CFG::CFG(const std::string& file) {
    ifstream input(file);

    json j;
    input >> j;

    for(auto production: j["Productions"]) {
        std::string head = production["head"];
        std::vector<std::string> replacements;
        for(const auto& replacement: production["body"]) {
            replacements.push_back(replacement);
        }
        if(replacements.empty()) {
            replacements.emplace_back("");
        }
        productionRules.insert({head, replacements});
    }
    startSymbol = j["Start"];
    for(const auto& terminal: j["Terminals"]) {
        terminals.insert((std::string) terminal);
    }
    for(const auto& variable: j["Variables"]) {
        variables.insert((std::string) variable);
    }
    for (const auto &alias : j["Aliases"]) {
        std::vector<std::wstring> v;
        for (const auto &a : alias["body"]) {
            std::string head = alias["head"];
            std::string body = a;
            std::wstring b(body.begin(), body.end());
            aliasMap.emplace(b, head);
            v.emplace_back(b);
        }
        aliases.emplace_back(v);
    }
}

bool CFG::accepts(const std::string& str) {
    CYK cyk(this);
    cyk(str);
    cyk.print();
    bool accepts = cyk.accepts();
    cout << boolalpha << accepts << endl;
    return accepts;
}

bool CFG::isVariable(const string &s) {
    return std::find(variables.begin(), variables.end(), s) != variables.end();
}

bool CFG::isTerminal(const string &s) {
    return std::find(terminals.begin(), terminals.end(), s) != terminals.end();
}

ProductionRules CFG::getRules(const string &head) {
    ProductionRules rules;
    for(auto& rule: productionRules) {
        if(rule.first == head)
            rules.insert(rule);
    }
    return rules;
}

const vector<std::vector<std::wstring>> &CFG::getAliases() const {
    return aliases;
}

const map<std::wstring, std::string> &CFG::getAliasMap() const {
    return aliasMap;
}
