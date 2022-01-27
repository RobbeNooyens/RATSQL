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

#include <iostream>
#include <algorithm>
#include <memory>
#include "ShuntingAlgorithm.h"
#include "../exceptions/ExceptionHandler.h"
#include "../parser/ParseTemplate.h"
#include "../parser/Tokens.h"

using namespace std;

void ShuntingAlgorithm::operator()(std::vector<ParseToken>& tokens, std::ostream& stream) {
    bool quoteOpen = false;
    for(auto& token: tokens) {
        if(!quoteOpen && token.getToken() == Tokens::QUOTE){
            quoteOpen = true;
            continue;
        } else if(quoteOpen && (token.getToken() == Tokens::NAME || token.getToken() == Tokens::DIGIT)) {
            token.enquote();
        } else if(quoteOpen && token.getToken() == Tokens::QUOTE) {
            quoteOpen = false;
            continue;
        }
        if(isOperator(token)) {
            consumeOperator(token);
        } else {
            consumeText(token);
        }
        printQueue();
        printOperatorStack();
        cout << endl;
    }
    flush();
    printQueue();
    parse(stream);

    grid.substitute();
}

void ShuntingAlgorithm::flush() {
    while(!operatorStack.empty()) {
        queue.push(operatorStack.top());
        operatorStack.pop();
    }
}

void ShuntingAlgorithm::consumeOperator(ParseToken &opSymbol) {
    if(opSymbol.getToken() == Tokens::ROUNDED_BRACKET_LEFT) {
        operatorStack.push(opSymbol);
        return;
    } else if(opSymbol.getToken() == Tokens::ROUNDED_BRACKET_RIGHT) {
        auto& stackTop = operatorStack.top();
        while(stackTop.getToken() != Tokens::ROUNDED_BRACKET_LEFT) {
            operatorStack.pop();
            queue.push(stackTop);
            stackTop = getStackTop();
        }
        operatorStack.pop();
        return;
    }
    if(operatorStack.empty()) {
        operatorStack.push(opSymbol);
        return;
    }
    int weight = precedence[opSymbol.getToken()];
    auto& stacktop = getStackTop();
    int weightStacktop = precedence[stacktop.getToken()];
    if(stacktop.getToken() == Tokens::EQUALS && operatorStack.size() == 1)
        weightStacktop = 30;
    if(weight >= weightStacktop) {
        queue.push(stacktop);
        operatorStack.pop();
        if(stacktop.getToken() == Tokens::PI && getStackTop().getToken() == Tokens::RHO) {
            queue.push(operatorStack.top());
            operatorStack.pop();
        }
    }
    operatorStack.push(opSymbol);
}


void ShuntingAlgorithm::consumeText(ParseToken &text) {
    queue.push(text);
    if(operatorStack.empty())
        return;
    auto& opToken = operatorStack.top().getToken();
//    if(opToken == Tokens::COMMA || opToken == Tokens::ARROW_LEFT || opToken == Tokens::LESS_THAN || opToken == Tokens::EQUALS) {
    if(precedence[opToken] == 1) {
        queue.push(operatorStack.top());
        operatorStack.pop();
    }
}

template <typename T>
void traverse_stack(stack<T> st) {
    while (!st.empty()) {
        try { cout << st.top() << endl; } catch (exception &e) {
            // typename T cannot be used by std::cout
            ExceptionHandler::handle(e,"An error occurred while trying to traverse the stack.");
            return;
        }
        st.pop();
    }
}

__attribute__((unused)) void ShuntingAlgorithm::printOperatorStack() {
    cout << "-- Operator stack:" << endl;
    traverse_stack(operatorStack);
}

__attribute__((unused)) void ShuntingAlgorithm::printQueue() {
    cout << "-- Queue:" << endl;
    for(int i = 0; i < queue.size(); i++) {
        auto& front = queue.front();
        queue.pop();
        queue.push(front);
        cout << front << endl;
    }
}

bool ShuntingAlgorithm::isOperator(ParseToken &symbol) {
    return any_of(precedence.begin(),precedence.end(),[symbol](const std::pair<std::string,int>& entry) { return entry.first == symbol.getToken(); });
}

ParseToken & ShuntingAlgorithm::getStackTop() {
    return operatorStack.empty() ? emptyToken : operatorStack.top();
}

void ShuntingAlgorithm::parse(ostream &stream, bool print) {
    // Creating a new variable for printing
    vector<string> output;

    // Algorithm
    ParseToken& queueFront = emptyToken;
    while(!queue.empty()) {
        queueFront = queue.front();
        if(isOperator(queueFront)) {
            // Operator found, parse!
            parseOperator(queueFront, output);
        } else {
            // No operator, add to the textStack
            textStack.push(queue.front());
        }
        // Pop the top of the queue and start over
        queue.pop();
    }
}

void ShuntingAlgorithm::parseOperator(ParseToken &queueFront, vector<string>& output) {
    auto& stackTop1 = textStack.top();
    textStack.pop();
    auto& stackTop2 = textStack.top();
    if (!textStack.empty()) textStack.pop();

    int index = 0;
    if(operatorTypes[queueFront.getToken()] == PREFIX) {
        // We have an operator that uses prefix
        index = grid.addExpression(queueFront, stackTop2, stackTop1);
    } else if(operatorTypes[queueFront.getToken()] == INFIX) {
        // Operator that uses infix
        index = grid.addExpression(stackTop2, queueFront, stackTop1);
    } else {
        // Operator that uses postfix
        index = grid.addExpression(stackTop2, stackTop1, queueFront);
    }

    textStack.push({Tokens::SUBSTITUTION, to_string(index)});
}

std::vector<std::vector<ParseToken>> ShuntingAlgorithm::getShuntingOutput() {
    return grid.substitute();
}