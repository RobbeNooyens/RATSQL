//
// Created by Cédric Leclercq on 25/11/2021.
//

#ifndef RATSQL_PARSETREE_H
#define RATSQL_PARSETREE_H

#include <memory>
#include "Node.h"

class ParseTree {
private:
    std::shared_ptr<Node> root;
public:
    std::shared_ptr<Node>& getRoot() const;
    void setRoot(const std::shared_ptr<Node> &nroot);
};


#endif //RATSQL_PARSETREE_H
