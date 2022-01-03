//
// Created by robnoo on 3/01/22.
//

#include <string>
#include <vector>
#include <utility>
#include "Tree.h"

Tree::Tree(std::string content): content(std::move(content)) {
}

Tree::~Tree() {
    for(auto& tree: children) {
        delete tree;
        tree = nullptr;
    }
    children.clear();
}

void Tree::addChild(Tree *tree) {
    children.push_back(tree);
}

Tree *Tree::getChild(int index) {
    return index >= children.size() ? nullptr : children[index];
}

std::vector<Tree *> &Tree::getChildren() {
    return children;
}

//void Tree::addChild(int option, Tree *tree) {
//    while(option >= children.size()) {
//        children.emplace_back();
//    }
//    children[option].push_back(tree);
//}
//
//Tree *Tree::getChild(int option, int index) {
//    return (option >= children.size() || index >= children[option].size()) ? nullptr : children[option][index];
//}
