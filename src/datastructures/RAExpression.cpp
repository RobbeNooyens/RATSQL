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

#include "RAExpression.h"
#include "../exceptions/ExceptionHandler.h"
#include <iostream>

void RAExpression::setWord(int index, const RAWord& word) {
    try {
        this->expression[index] = word;
    } catch (std::exception& exc) {
        const std::string& error = "Error in RAExpression::setWord(int index, const std::string& word): An index that does not exist was given.";
        ExceptionHandler::handle(exc, error);
    }
}

RAWord RAExpression::getWord(int index) {
    try {
        return this->expression[index];
    } catch (std::exception& exc) {
        const std::string& error = "Error in RAExpression::getWorld(int index): An index that does not exist was given.";
        ExceptionHandler::handle(exc, error);
    }
    return {};
}

void RAExpression::printExpression(std::ostream &stream) {
    int index = 0;
    for(auto& s: this->expression) {
        std::string toPrint{};
        for (auto& elem: s) {
            toPrint += elem + " ";
            if (elem == s.back()) toPrint.pop_back();
        }
        stream << index << ": " << toPrint << std::endl;
        index++;
    }
}

RAExpression::RAExpression(const std::vector<std::string>& expression) {
    auto word = RAWord();

}

std::vector<RAWord> RAExpression::getExpression() const {
    return this->expression;
}

void RAExpression::addWord(const RAWord &word) {
    expression.push_back(word);
}
