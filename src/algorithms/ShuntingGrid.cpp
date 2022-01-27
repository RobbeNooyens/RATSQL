//
// Created by robnoo on 27/01/22.
//

#include <algorithm>
#include "ShuntingGrid.h"
#include "../parser/Tokens.h"

using namespace std;

bool isPrefixOperator(const string &str) {
    return str == Tokens::PI || str == Tokens::SIGMA || str == Tokens::RHO;
}

int ShuntingGrid::addExpression(ParseToken &t1, ParseToken &t2, ParseToken &t3) {
    vector<ParseToken> tokens = {t1, t2, t3};
    int index = -1;
    for(int i = 0; i < grid.size(); i++) {
        if(grid[i] == tokens) {
            index = i;
        }
    }
    if(index == -1) {
        index = (int) grid.size();
        grid.push_back(tokens);
    }
    return index;
}

void ShuntingGrid::substitute(vector<ParseToken>& current, int row) {
    int colId = 0;
    string rowType = grid.at(row).front().getToken();
    bool skipBrackets = false;
    for(auto& token: grid.at(row)) {
        if(token.getToken() == Tokens::SUBSTITUTION) {
            int id = stoi(token.getContent());
            string firstToken = grid.at(id).front().getToken();
            if(usages.at(id) > 1 && isPrefixOperator(firstToken)) {
                current.emplace_back(Tokens::NAME, firstToken + to_string(id));
            } else {
                substitute(current, id);
            }
        } else {
            current.push_back(token);
        }
        colId++;
        if(isPrefixOperator(rowType)) {
            if(colId == 2) {
                if(grid.at(row).at(colId).getToken() == Tokens::SUBSTITUTION) {
                    int otherRow = stoi(grid.at(row).at(colId).getContent());
                    skipBrackets = isPrefixOperator(grid.at(otherRow).front().getToken());
                }
                if(!skipBrackets)
                    current.emplace_back(Tokens::ROUNDED_BRACKET_LEFT, "(");
            }
            else if(colId == 3 && !skipBrackets)
                current.emplace_back(Tokens::ROUNDED_BRACKET_RIGHT, ")");
        }
    }
}

vector<vector<ParseToken>> ShuntingGrid::substitute() {
    calculateUsages();

    vector<vector<ParseToken>> result;

    // Substitute main expression
    vector<ParseToken> start;
    substitute(start, static_cast<int>(grid.size() - 1));
    result.push_back(start);

    // Substitute variables
    for(int i = 0; i < grid.size(); i++) {
        auto& firstToken = grid.at(i).front().getToken();
        if(usages.at(i) > 1 && (firstToken == Tokens::PI || firstToken == Tokens::SIGMA)) {
            vector<ParseToken> expression;
            expression.emplace_back(Tokens::NAME, firstToken + to_string(i));
            expression.emplace_back(Tokens::EQUALS, "=");
            substitute(expression, i);
            result.push_back(expression);
        }
    }

    std::reverse(result.begin(), result.end());

    return result;
}

void ShuntingGrid::calculateUsages() {
    usages.clear();
    for(auto& row: grid) {
        usages.push_back(0);
    }
    for(auto& row: grid) {
        for(auto& token: row) {
            if(token.getToken() == Tokens::SUBSTITUTION) {
                usages[stoi(token.getContent())]++;
            }
        }
    }
}
