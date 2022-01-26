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
    for(auto& token: tokens) {
        consume(token);
        printQueue();
        printOperatorStack();
        cout << endl;
    }
    flush();
    printQueue();
    parse(stream);
}


void ShuntingAlgorithm::consume(ParseToken& token) {
    if(isOperator(token)) {
        consumeOperator(token);
    } else {
        consumeText(token);
    }
}

void ShuntingAlgorithm::flush() {
    while(!operatorStack.empty()) {
        queue.push(operatorStack.top());
        operatorStack.pop();
    }
    expression = RAExpression();
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
    if(opToken == Tokens::COMMA || opToken == Tokens::ARROW_LEFT || opToken == Tokens::LESS_THAN) {
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

RAExpression ShuntingAlgorithm::parse(ostream &stream, bool print) {
    // Creating a new expression for saving
    expression = RAExpression();
    // Creating a new variable for printing
    vector<string> output;

    // todo algorithm: count the amount of times a table entry occurs + take the amounts into account
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

    // Printing the result if asked to do so
    if (print) expression.printExpression(stream);
    return expression;
}

RAExpression ShuntingAlgorithm::getRAExpression() const {
    return this->expression;
}

void ShuntingAlgorithm::parseOperator(ParseToken &queueFront, vector<string>& output) {
    auto& stackTop1 = textStack.top();
    textStack.pop();
    auto& stackTop2 = textStack.top();
    if (!textStack.empty()) textStack.pop();

    string joined;
    std::shared_ptr<RAWord> word;
    if(operatorTypes[queueFront.getToken()] == PREFIX) {
        // We have an operator that uses prefix
        word = std::make_shared<RAWord>(std::vector<ParseToken>{queueFront, stackTop2, stackTop1});
        joined = queueFront.getContent();
        joined.append(" ").append(stackTop2.getContent()).append(" ").append(stackTop1.getContent());
    } else if(operatorTypes[queueFront.getToken()] == INFIX) {
        // Operator that uses infix
        word = std::make_shared<RAWord>(std::vector<ParseToken>{stackTop2, queueFront, stackTop1});
        joined = stackTop2.getContent();
        joined.append(" ").append(queueFront.getContent()).append(" ").append(stackTop1.getContent());
    } else {
        // Operator that uses postfix
        word = std::make_shared<RAWord>(std::vector<ParseToken>{stackTop2, stackTop1, queueFront});
        joined = stackTop2.getContent();
        joined.append(" ").append(stackTop1.getContent()).append(" ").append(queueFront.getContent());
    }

    int index = -1;
    for(int i = 0; i < output.size(); i++) {
        if(output[i] == joined) {
            index = i;
        }
    }
    if(index == -1) {
        index = (int) output.size();
        expression.addWord(word);
        output.push_back(joined);
    }
    textStack.push({Tokens::SUBSTITUTION, to_string(index)});
}
