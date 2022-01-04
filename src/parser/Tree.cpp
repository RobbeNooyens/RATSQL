//
// Created by robnoo on 3/01/22.
//

#include <string>
#include <utility>
#include <vector>
#include <utility>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include "Tree.h"

using std::endl;

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

Tree::Tree(std::string token): token(std::move(token)), value("") {

}

void Tree::assignTokens(const std::vector<ParseToken> &tokens, int &tokenIndex) {
    if(tokenIndex >= tokens.size())
        throw std::runtime_error("Index can't be bigger than tokensize");
    if(children.empty()) {
        value = tokens[tokenIndex++].getContent();
    } else {
        for(auto& child: children) {
            child->assignTokens(tokens, tokenIndex);
        }
    }
}

void Tree::exportDot(std::string &fileName) {
    assert(!fileName.empty());
    std::ofstream file;
    file.open(fileName.c_str());
    assert(file.is_open());

    // Export begin
    file << "digraph ParseTree {" << endl;
//    file << "  rankdir = \"LR\";" << endl;

    int index = 0;
    exportDotRecursive(file, index);

    // Export end
    file << "}" << endl;

    file.close();
    assert(!file.is_open());

}

void Tree::exportDotRecursive(std::ofstream &out, int& index) {
    int currentIndex = index++;
    out << "  " << currentIndex << " [label=\"" << token << "\"]" << ";" << std::endl;
    for(auto& child: children) {
        out << "  " << currentIndex << " -> " << index << std::endl;
        child->exportDotRecursive(out, index);
    }

}
