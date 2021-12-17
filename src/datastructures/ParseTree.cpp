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

std::wstring ParseTree::getYield() const {
    try {
        assert(this->getRoot().use_count() != 0);
    } catch (std::exception &exc) {
        std::wcerr << exc.what() << std::endl;
        return std::wstring{};
    }
    std::wstring yield;
    return this->inorderTraversalYield(this->getRoot(), yield);
}

std::wstring ParseTree::inorderTraversalYield(const std::shared_ptr<Node> &node, std::wstring &oYield) const {
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


