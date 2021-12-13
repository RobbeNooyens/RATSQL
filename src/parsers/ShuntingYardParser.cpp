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

using namespace std;

ShuntingYardParser::ShuntingYardParser() = default;

void ShuntingYardParser::consume(string &symbol) {
    std::cout << "Consuming [" << symbol << "]" << std::endl;
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
}

void ShuntingYardParser::consumeOperator(string &opSymbol) {
    if(opSymbol == "(") {
        operatorStack.push(opSymbol);
        return;
    } else if(opSymbol == ")") {
        printOperatorStack();
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
void traverse_stack(stack<T> & st) {
    if(st.empty())
        return;
    T x = st.top();
    cout << x << endl;
    st.pop();
    traverse_stack(st);
    st.push(x);
}

void ShuntingYardParser::printOperatorStack() {
    cout << "Operator stack:" << endl;
    traverse_stack(operatorStack);
}

void ShuntingYardParser::printQueue() {
    cout << "Queue:" << endl;
    for(int i = 0; i < queue.size(); i++) {
        string front = queue.front();
        queue.pop();
        queue.push(front);
        cout << front << endl;
    }
}

bool ShuntingYardParser::isOperator(string &symbol) {
    for(const auto& entry: precedence) {
        if(entry.first == symbol)
            return true;
    }
    return false;
}

string &ShuntingYardParser::getStackTop() {
    return operatorStack.empty() ? emptyStack : operatorStack.top();
}

void ShuntingYardParser::generateOutput(ostream &stream) {
    vector<string> combined;
    string queueFront;
    while(!queue.empty()) {
        queueFront = queue.front();
        if(isOperator(queueFront)) {
            string stackTop1 = textStack.top();
            textStack.pop();
            string stackTop2 = textStack.top();
            textStack.pop();
            // TODO: error handling
            string joined;
            if(operatorTypes[queueFront] == PREFIX) {
                joined = queueFront.append(" ").append(stackTop2).append(" ").append(stackTop1);
            } else if(operatorTypes[queueFront] == INFIX) {
                joined = stackTop2.append(" ").append(queueFront).append(" ").append(stackTop1);
            } else {
                joined = stackTop2.append(" ").append(stackTop1).append(" ").append(queueFront);
            }
            int index = -1;
            for(int i = 0; i < combined.size(); i++) {
                if(combined[i] == joined) {
                    index = i;
                }
            }
            if(index == -1) {
                index = (int) combined.size();
                combined.push_back(joined);
            }
            textStack.push(to_string(index));
        } else {
            textStack.push(queueFront);
        }
        queue.pop();
    }
    int index = 0;
    for(auto& s: combined) {
        stream << index << ": " << s << endl;
        index++;
    }
}
