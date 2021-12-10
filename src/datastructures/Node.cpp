/**
 *  ╒══════════════════════════════════════════════════╕
 *  │                                                  │
 *  │                 RATSQL Project                   │
 *  │            Relational Algebra To SQL             │
 *  │                                                  │
 *  │  Contributors: Pablo Deputter, Cédric Leclercq,  │
 *  │               Robbe Nooyens, Maarten Peirsman    │
 *  │                                                  │
 *  │   University of Antwerp - Advanced Programming   │
 *  │                                                  │
 *  ╘══════════════════════════════════════════════════╛
 */

#include "Node.h"

std::string Node::getData() {
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

void Node::addOperation(const std::string &var1, const std::string &oper, const std::string &var2) {
    this->leftVar = std::shared_ptr<Node>(new Node(var1));
    this->middleVar = std::shared_ptr<Node>(new Node(oper));
    this->rightVar = std::shared_ptr<Node>(new Node(var2));
}



