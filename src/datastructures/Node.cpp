//
// Created by Cédric Leclercq on 25/11/2021.
//

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

void Node::setLeftVar(const std::shared_ptr<Node> &nLeftVar) {
    assert(nLeftVar.use_count() != 0);
    this->leftVar = nLeftVar;
}

void Node::setMiddleVar(const std::shared_ptr<Node> &nMiddleVar) {
    assert(nMiddleVar.use_count() != 0);
    this->middleVar = nMiddleVar;
}

void Node::setRightVar(const std::shared_ptr<Node> &nRightVar) {
    assert(nRightVar.use_count() != 0);
    this->rightVar = nRightVar;
}

void Node::addOperation(const std::string &var1, const std::string &oper, const std::string &var2) {
    this->setLeftVar(std::shared_ptr<Node>(new Node(var1)));
    this->setMiddleVar(std::shared_ptr<Node>(new Node(oper)));
    this->setRightVar(std::shared_ptr<Node>(new Node(var2)));
}



