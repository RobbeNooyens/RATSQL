//
// Created by Cédric Leclercq on 25/11/2021.
//

#ifndef RATSQL_NODE_H
#define RATSQL_NODE_H

#include <string>

class Node {
    std::string data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> middle;
};


#endif //RATSQL_NODE_H
