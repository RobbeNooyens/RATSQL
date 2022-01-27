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

const string &TreeNode::getToken() const {
    return token;
}

const string &TreeNode::getValue() const {
    return value;
}

std::string BasicNode::translate() const {
    std::string output = value;
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
    for (auto child = children.rbegin(); child != children.rend(); ++child) {
        (*child)->translate(v);
    }

    // Check the contents of the vector
    if (v[1].empty()) {
        v[1] = "SELECT * FROM ";
    }
    if (v[2].empty()) {
        // Todo: throw error saying a table should be specified
    }
    std::string output;
    for (const auto &s : v) {
        output += s;
    }
    return output;
}

void ExpressionNode::translate(vector<std::string> &v) const {
    v[2] += translate();
}

ModificationNode::ModificationNode(const string &token): TreeNode(token) {}

void ModificationNode::translate(vector<std::string> &v) const {
    for (auto child = children.rbegin(); child != children.rend(); ++child) {
        (*child)->translate(v);
        const TreeNode *node = *child;
    }
}

SelectionNode::SelectionNode(const string &token): TreeNode(token) {}

void SelectionNode::translate(vector<std::string> &v) const {
//    static int tempTableCount = 0;
    std::string output;
    for (auto child : children) {
        output += child->translate();
    }
    std::string where = " WHERE ";
//    if (!v[3].empty()) {
//        std::string tempTableName = "TempTable" + to_string(tempTableCount);
//        std::string tempTable = ") AS " + tempTableName;
//        where.insert(where.begin(), tempTable.begin(), tempTable.end());
//    }
    v[3] += where + output;
}

BasicNode::BasicNode(const std::string &token): TreeNode(token) {}

ProjectionNode::ProjectionNode(const string &token): TreeNode(token) {}

void ProjectionNode::translate(vector<std::string> &v) const {
    static int tableNumber;
    std::string output = "SELECT ";
    for (auto child: children) {
        output += child->translate();
    }
    output += " FROM ";
    if (!v[1].empty()) {
        output += "(";
        std::string tempTableName = "TempTable" + to_string(tableNumber++);
        std::string tempTable = ") AS " + tempTableName;
        v[3] += tempTable;
    }
    v[1].insert(v[1].begin(), output.begin(), output.end());
}

TableNode::TableNode(const string &token): TreeNode(token) {}

void TableNode::translate(vector<std::string> &v) const {
    v[2] += translate();
}

std::string TableNode::translate() const {
    std::string output;
    for (auto child : children) {
        output += child->translate();
    }
    // Filter out brackets
    for (int i = 0; i < output.size(); ++i) {
        auto c = output.begin() + i;
        if (*c == '(' || *c == ')') {
            output.erase(c);
            --i;
        }
    }
    return output;
}

ValueNode::ValueNode(const string &token): TreeNode(token) {}

std::string ValueNode::translate() const {
    return token;
}

RenameNode::RenameNode(const string &token): TreeNode(token) {}

void RenameNode::translate(vector<std::string> &v) const {
    std::string output;
    for (int i = 1; i < v.size(); ++i) {
        output += v[i]; // Write the string
        v[i].clear(); // Empty the string
    }
    v[0] += output + "\n";
}
