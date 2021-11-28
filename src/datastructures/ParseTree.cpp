//
// Created by Cédric Leclercq on 25/11/2021.
//

#include "ParseTree.h"

const std::shared_ptr<Node> &ParseTree::getRoot() const {
    return this->root;
}

std::string ParseTree::getYield() const {
    try {
        assert(this->getRoot().use_count() != 0);
    } catch(std::exception& exc) {
        // TODO
    }
    std::string yield;
    return this->inorderTraversalYield(this->getRoot(), yield);
}

std::string ParseTree::inorderTraversalYield(const std::shared_ptr<Node>& node, std::string& oYield) const {
    if (node->getLeftVar() != nullptr)
        inorderTraversalYield(node->getLeftVar(), oYield); // First search left node

    if (node->getMiddleVar() != nullptr)
        inorderTraversalYield(node->getMiddleVar(), oYield); // Then search middle node

    if (node->getRightVar() != nullptr)
        inorderTraversalYield(node->getRightVar(), oYield); // Lastly, search right node

    if (node->getLeftVar() == nullptr and node->getRightVar() == nullptr)
        oYield += node->getData(); // We want the yield, so only the nodes with no children can give their data

    return oYield;
}


