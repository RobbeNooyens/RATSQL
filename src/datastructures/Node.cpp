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

#include "Node.h"

const Token & Node::getData() {
    return this->data;
}

std::shared_ptr<Node> Node::getLeftVar() const {
    return this->leftVar;
}

std::shared_ptr<Node> Node::getMiddleVar() const {
    return this->middleVar;
}

std::shared_ptr<Node> Node::getRightVar() const {
    return this->rightVar;
}

void Node::addOperation(const Token &var1, const Token &oper, const Token &var2) {
    this->leftVar = std::shared_ptr<Node>(new Node(var1));
    this->middleVar = std::shared_ptr<Node>(new Node(oper));
    this->rightVar = std::shared_ptr<Node>(new Node(var2));
}

Node::Node(const Token &nData): data(move(nData)) {}



