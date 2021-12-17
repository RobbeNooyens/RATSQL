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
#include <cassert>
#include "ParseTree.h"

const std::shared_ptr<Node> &ParseTree::getRoot() const {
    return this->root;
}

std::string ParseTree::getYield() const {
    try {
        assert(this->getRoot().use_count() != 0);
    } catch (std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return std::string{};
    }
    std::string yield;
    return this->inorderTraversalYield(this->getRoot(), yield);
}

std::string ParseTree::inorderTraversalYield(const std::shared_ptr<Node> &node, std::string &oYield) const {
    if (node->getLeftVar() != nullptr)
        inorderTraversalYield(node->getLeftVar(), oYield); // First search left node

    if (node->getMiddleVar() != nullptr)
        inorderTraversalYield(node->getMiddleVar(), oYield); // Then search middle node

    if (node->getRightVar() != nullptr)
        inorderTraversalYield(node->getRightVar(), oYield); // Lastly, search right node

    if (node->getLeftVar() == nullptr and node->getRightVar() == nullptr)
        oYield += node->getData().getContent(); // We want the yield, so only the nodes with no children can give their data

    return oYield;
}

ParseTree::ParseTree(const Node &n) {
    root = std::make_shared<Node>(n);
}


