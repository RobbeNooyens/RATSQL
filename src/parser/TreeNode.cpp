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
#include "TreeNode.h"

using std::endl;

TreeNode::~TreeNode() {
    for(auto& tree: children) {
        delete tree;
        tree = nullptr;
    }
    children.clear();
}

void TreeNode::addChild(TreeNode *tree) {
    children.push_back(tree);
}

TreeNode *TreeNode::getChild(int index) {
    return index >= children.size() ? nullptr : children[index];
}

const std::vector<TreeNode *> &TreeNode::getChildren() const {
    return children;
}

TreeNode::TreeNode(std::string token): token(std::move(token)), value("") {

}

void TreeNode::assignTokens(const std::vector<ParseToken> &tokens, int &tokenIndex) {
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

void TreeNode::exportDot(std::string &fileName) {
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

void TreeNode::exportDotRecursive(std::ofstream &out, int& index) {
    int currentIndex = index++;
    out << "  " << currentIndex << " [label=\"" << token << "\"]" << ";" << std::endl;
    for(auto& child: children) {
        out << "  " << currentIndex << " -> " << index << std::endl;
        child->exportDotRecursive(out, index);
    }

}

std::string TreeNode::translate() const {
    std::string output;
    auto t = token;
    for (auto child : children) {
        output += child->translate();
    }
    return output;
}

ExpressionNode::ExpressionNode(const string &token): TreeNode(token) {}

std::string ExpressionNode::translate() const {
    std::vector<std::string> v;
    v.reserve(4);
    for (int i = 0; i < 4; ++i) {
        v.emplace_back("");
    }
    for (auto child : children) {
        child->translate(v);
    }

    // Check the contents of the vector
    if (v[0].empty()) {
        v[0] = "SELECT *";
    }
    if (v[1].empty()) {
        // Todo: throw error saying a table should be specified
    } else {
        std::string from = "FROM ";
        v[1].insert(v[1].begin(), from.begin(), from.end());
    }
    std::string output;
    for (const auto &s : v) {
        output += s + " ";
    }
    return output;
}

void ExpressionNode::translate(vector<std::string> &v) const {
    v[1] += translate();
}

SelectionNode::SelectionNode(const string &token): TreeNode(token) {}

void SelectionNode::translate(vector<std::string> &v) const {
    std::string output;
    for (auto child : children) {
        output += child->translate();
    }
    v[4] += "WHERE " + output;
}

BasicNode::BasicNode(const std::string &token): TreeNode(token) {}

std::string BasicNode::translate() const {
    std::string output = value;
    for (auto child : children) {
        output += child->translate();
    }
    return output;
}

ModificationNode::ModificationNode(const string &token): TreeNode(token) {}

void ModificationNode::translate(vector<std::string> &v) const {
    for (auto child : children) {
        child->translate(v);
    }
}

ProjectionNode::ProjectionNode(const string &token): TreeNode(token) {}

void ProjectionNode::translate(vector<std::string> &v) const {
    std::string output = "SELECT ";
    for (auto child: children) {
        output += child->translate();
    }
    v[0] += output;
}

TableNode::TableNode(const string &token): TreeNode(token) {}

void TableNode::translate(vector<std::string> &v) const {
    v[1] += translate();
}

std::string TableNode::translate() const {
    std::string output;
    for (auto child : children) {
        output += child->translate();
    }
    return output;
}
