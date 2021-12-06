//
// Created by Cédric Leclercq on 29/11/2021.
//

#include <iostream>
#include "ShuntingYardParser.h"

using namespace std;

ShuntingYardParser::ShuntingYardParser() = default;

void ShuntingYardParser::consume(string &symbol) {
    std::cout << "Consuming [" << symbol << "]" << std::endl;
    if(tokens.find(symbol) != tokens.end()) {

    }
}

void ShuntingYardParser::flush() {

}

void ShuntingYardParser::consumeOperator(string &opSymbol) {

}

void ShuntingYardParser::consumeText(string &text) {

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
