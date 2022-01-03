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

void RAExpression::setWord(int index, const std::string& word) {
    try {
        this->expression[index] = word;
    } catch (std::exception& exc) {
        const std::string& error = "Error in RAExpression::setWord(int index, const std::string& word): An index that does not exist was given.";
        ExceptionHandler::handle(exc, error);
    }
}

std::string RAExpression::getWord(int index) {
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
        stream << index << ": " << s << std::endl;
        index++;
    }
}

RAExpression::RAExpression(std::vector<std::string> expression) {
    this->expression = std::move(expression);
}

std::vector<std::string> RAExpression::getExpression() const {
    return this->expression;
}
