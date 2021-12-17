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

#ifndef RATSQL_PARSETREE_H
#define RATSQL_PARSETREE_H

#include <memory>
#include "Node.h"

class ParseTree {
private:
    /// Root of the parse tree - a shared pointer to a Node object
    std::shared_ptr<Node> root;
    /**
     * Recursive function. Calculates the yield of the param node with the use of inorder traversal.
     * @param node          current node it is doing the traverse of
     * @param oYield        the yield it already found
     * @return std::string  the yield of param node
     */
    std::wstring inorderTraversalYield(const std::shared_ptr<Node>& node, std::wstring& oYield) const;
public:
    /**
     * Constructor boi
     */
    ParseTree()=default;

    /**
     * Better constructor boi
     * @param n root node
     */
    ParseTree(const Node &n);

    /**
     * Gets the root of this parse tree
     * @return std::shared_ptr<Node>&   A shared pointer to the root of this parse tree
     */
    const std::shared_ptr<Node>& getRoot() const;
    /**
     * Will return the yield of a parse tree. Makes use of a recursive function.
     * @return  std::string     The yield of this parse tree
     */
    std::wstring getYield() const;
};


#endif //RATSQL_PARSETREE_H
