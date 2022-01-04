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

#include <sstream>
#include <iostream>
#include <algorithm>
#include "ShuntingAlgorithm.h"
#include "../exceptions/ExceptionHandler.h"
using namespace std;

void ShuntingAlgorithm::operator()(string &str, std::ostream& stream) {
    stringstream strStream;
    for(char c: str) {
        if(c == ' ') { // todo the error of the spaces around the error is here - can't use space to separate items!
            string token = strStream.str();
            consume(token);
            strStream.str(string());
        } else {
            strStream << c;
        }
    }
    if(!strStream.str().empty()) {
        string token = strStream.str();
        consume(token);
    }
    flush();
    parse(stream);
}


void ShuntingAlgorithm::consume(string &symbol) {
    if(isOperator(symbol)) {
        consumeOperator(symbol);
    } else {
        consumeText(symbol);
    }
}

void ShuntingAlgorithm::flush() {
    while(!operatorStack.empty()) {
        queue.push(operatorStack.top());
        operatorStack.pop();
    }
    expression = RAExpression();
}

void ShuntingAlgorithm::consumeOperator(string &opSymbol) {
    if(opSymbol == "(") {
        operatorStack.push(opSymbol);
        return;
    } else if(opSymbol == ")") {
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

void ShuntingAlgorithm::consumeText(string &text) {
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

__attribute__((unused)) void ShuntingAlgorithm::printOperatorStack() {
    cout << "Operator stack:" << endl;
    traverse_stack(operatorStack);
}

__attribute__((unused)) void ShuntingAlgorithm::printQueue() {
    cout << "Queue:" << endl;
    for(int i = 0; i < queue.size(); i++) {
        string front = queue.front();
        queue.pop();
        queue.push(front);
        cout << front << endl;
    }
}

bool ShuntingAlgorithm::isOperator(string &symbol) {
    return any_of(precedence.begin(),precedence.end(),[symbol](const std::pair<std::string,int>& entry) { return entry.first == symbol; });
}

string &ShuntingAlgorithm::getStackTop() {
    return operatorStack.empty() ? emptyString : operatorStack.top();
}

RAExpression ShuntingAlgorithm::parse(ostream &stream, bool print) {
    // Creating a new expression for saving
    expression = RAExpression();
    // Creating a new variable for printing
    vector<string> output;

    // todo algorithm: count the amount of times a table entry occurs + take the amounts into account
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

RAExpression ShuntingAlgorithm::getRAExpression() const {
    return this->expression;
}

void ShuntingAlgorithm::parseOperator(string &queueFront, vector<string>& output) {
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
