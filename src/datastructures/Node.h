//
// Created by Cédric Leclercq on 25/11/2021.
//

#ifndef RATSQL_NODE_H
#define RATSQL_NODE_H

#include <string>
#include <memory>

class Node {
private:
    /// Data of a node
    std::string data;
    /// Shared pointer to the node left to the current one
    std::shared_ptr<Node> leftVar;
    /// Shared pointer to the node middle to the current one
    std::shared_ptr<Node> middleVar;
    /// Shared pointer to the node right of the current one
    std::shared_ptr<Node> rightVar;
public:
    /**
     * Mr. constructo
     * @param nData     The data this node with get
     */
    explicit Node(const std::string& nData) {
        this->data = nData;
    }
    /**
     * Gets the data of the string
     * @return std::string      Returns the data of a node - a string
     */
    std::string getData();
    /**
     * Gets the node left of the current one
     * @return std::shared_ptr<Node>    Shared pointer to the left node
     */
    std::shared_ptr<Node> getLeftVar() const;
    /**
     * Gets the node in the middle of the current one
     * @return std::shared_ptr<Node>    Shared pointer to the middle node
     */
    std::shared_ptr<Node> getMiddleVar() const;
    /**
     * Gets the node right of the current one
     * @return std::shared_ptr<Node>    Shared pointer to the right node
     */
    std::shared_ptr<Node> getRightVar() const;
    /**
     * Adds an operation to a node.
     * Left node := Node(var1)
     * Middle node := Node(oper)
     * Right node := Node(var2)
     * @param var1
     * @param oper
     * @param var2
     */
    void addOperation(const std::string& var1, const std::string& oper, const std::string& var2);
};


#endif //RATSQL_NODE_H
