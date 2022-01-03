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
#include "ShuntingYardParser.h"
#include "../exceptions/ExceptionHandler.h"

using namespace std;

void ShuntingYardParser::consume(string &symbol) {
    //std::cout << "Consuming [" << symbol << "]" << std::endl; // todo remove debug
    if(isOperator(symbol)) {
        consumeOperator(symbol);
    } else {
        consumeText(symbol);
    }
}

void ShuntingYardParser::flush() {
    while(!operatorStack.empty()) {
        queue.push(operatorStack.top());
        operatorStack.pop();
    }
    expression = RAExpression();
}

void ShuntingYardParser::consumeOperator(string &opSymbol) {
    if(opSymbol == "(") {
        operatorStack.push(opSymbol);
        return;
    } else if(opSymbol == ")") {
        //printOperatorStack(); // todo remove debug
        std::string stackTop = operatorStack.top();
        while(stackTop != "(") {
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
    int weight = precedence[opSymbol];
    string stacktop = getStackTop();
    int weightStacktop = precedence[stacktop];
    if(weight >= weightStacktop) {
        queue.push(stacktop);
        operatorStack.pop();
        if(stacktop == "π" && getStackTop() == "ρ") {
            queue.push(operatorStack.top());
            operatorStack.pop();
        }
    }
    operatorStack.push(opSymbol);
}

void ShuntingYardParser::consumeText(string &text) {
    queue.push(text);
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

__attribute__((unused)) void ShuntingYardParser::printOperatorStack() {
    cout << "Operator stack:" << endl;
    traverse_stack(operatorStack);
}

__attribute__((unused)) void ShuntingYardParser::printQueue() {
    cout << "Queue:" << endl;
    for(int i = 0; i < queue.size(); i++) {
        string front = queue.front();
        queue.pop();
        queue.push(front);
        cout << front << endl;
    }
}

bool ShuntingYardParser::isOperator(string &symbol) {
    if(any_of(precedence.begin(),precedence.end(),[symbol](const std::pair<std::string,int>& entry) { return entry.first == symbol; })) {
        return true;
    }
    return false;
}

string &ShuntingYardParser::getStackTop() {
    return operatorStack.empty() ? emptyStack : operatorStack.top();
}

RAExpression ShuntingYardParser::parse(ostream &stream, bool print) {
    // Creating a new expression for saving
    expression = RAExpression();
    // Creating a new variable for printing
    vector<string> output;

    // Algorithm
    string queueFront;
    while(!queue.empty()) {
        queueFront = queue.front();
        if(isOperator(queueFront)) {
            // Operator found, parse!
            parseOperator(queueFront, output);
        } else {
            // No operator, add to the textStack
            textStack.push(queueFront);
        }
        // Pop the top of the queue and start over
        queue.pop();
    }

    // Printing the result if asked to do so
    if (print) expression.printExpression(stream);
    return expression;
}

RAExpression ShuntingYardParser::getRAExpression() const {
    return this->expression;
}

void ShuntingYardParser::parseOperator(string &queueFront, vector<string>& output) {
    string stackTop1 = textStack.top();
    textStack.pop();
    string stackTop2 = textStack.top();
    if (!textStack.empty()) textStack.pop();

    string joined;
    RAWord word;
    if(operatorTypes[queueFront] == PREFIX) {
        // We have an operator that uses prefix
        word = {queueFront, stackTop2, stackTop1};
        joined = queueFront.append(" ").append(stackTop2).append(" ").append(stackTop1);
    } else if(operatorTypes[queueFront] == INFIX) {
        // Operator that uses infix
        word = {stackTop2, queueFront, stackTop1};
        joined = stackTop2.append(" ").append(queueFront).append(" ").append(stackTop1);
    } else {
        // Operator that uses postfix
        word = {stackTop2, stackTop1, queueFront};
        joined = stackTop2.append(" ").append(stackTop1).append(" ").append(queueFront);
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
    textStack.push(to_string(index));
}
