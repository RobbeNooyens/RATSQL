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
#include "../parser/ParseTemplate.h"

void RAExpression::setWord(int index, const std::shared_ptr<RAWord>& word) {
    try {
        this->expression[index] = word;
    } catch (std::exception& exc) {
        const std::string& error = "Error in RAExpression::setWord(int index, const std::string& word): An index that does not exist was given.";
        ExceptionHandler::handle(exc, error);
    }
}

std::shared_ptr<RAWord> RAExpression::getWord(int index) {
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
        for (auto& elem: *s) {
            toPrint += elem.getContent() + " ";
            if (elem.getContent() == s->back().getContent()) toPrint.pop_back();
        }
        stream << index << ": " << toPrint << std::endl;
        index++;
    }
}

RAExpression::RAExpression(const std::vector<std::string>& expression) {
    auto word = RAWord();

}

std::vector<std::shared_ptr<RAWord>> RAExpression::getExpression() const {
    return this->expression;
}

void RAExpression::addWord(std::shared_ptr<RAWord> &word) {
    expression.push_back(word);
}

RAExpression::RAExpression(const std::vector<ParseToken> &expression) {
    // TODO: make RAExpression work with ParseTokens

}

bool RAExpression::operator==(const RAExpression &rhs) const {
    return expression == rhs.expression;
}
