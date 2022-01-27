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

BasicNode::BasicNode(const std::string &token): TreeNode(token) {}

std::string BasicNode::translate() const {
    std::string output = value;
    for (auto child : children) {
        output += child->translate();
    }
    return output;
}

ExpressionNode::ExpressionNode(const string &token): TreeNode(token) {}

unsigned int ExpressionNode::tempTableNumber = 0;

std::string ExpressionNode::lastTable;

std::string ExpressionNode::translate() const {
    auto iter = children.rbegin();
    std::vector<std::string> v;
    v.reserve(4);
    for (int i = 0; i < 4; ++i) {
        v.emplace_back("");
    }
    std::string lastTable = (*iter++)->translate(v);
    if (iter != children.rend()) {
        // There are modifications to the table
        lastTable = (*iter)->translate(v);
    }
//    for (auto child = children.rbegin(); child != children.rend(); ++child) {
//        (*child)->translate(v);
//    }

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

std::string ExpressionNode::translate(vector<std::string> &v) {
    v[2] += translate();
    return "";
}

void ExpressionNode::createView(vector<string> &v) {
    std::string output;
    std::string tempTable = "TempTable" + to_string(tempTableNumber++);
    if (v[1].empty()) {
        v[1] = "SELECT * FROM ";
    }
    for (int i = 1; i < v.size(); ++i) {
        output += v[i]; // Write the string
        v[i].clear(); // Empty the string
    }
    v[0] += "CREATE VIEW " + tempTable + " AS (" + output + ");\n";
    output.clear();
    lastTable = tempTable;
    v[2] = lastTable;
}

ModificationNode::ModificationNode(const string &token): ExpressionNode(token) {}

std::string ModificationNode::translate(vector<std::string> &v) {
    for (auto child = children.rbegin(); child != children.rend(); ++child) {
        (*child)->translate(v);
        const TreeNode *node = *child;
    }
    return "";
}

SelectionNode::SelectionNode(const string &token): ModificationNode(token) {}

std::string SelectionNode::translate(vector<std::string> &v) {
//    static int tempTableCount = 0;
    std::string output;
    for (auto child : children) {
        output += child->translate();
    }
    std::string where = " WHERE ";
    if (!v[3].empty()) {
        createView(v);
    }
//    if (!v[3].empty()) {
//        std::string tempTableName = "TempTable" + to_string(tempTableCount);
//        std::string tempTable = ") AS " + tempTableName;
//        where.insert(where.begin(), tempTable.begin(), tempTable.end());
//    }
    v[3] += where + output;
    return "";
}

ProjectionNode::ProjectionNode(const string &token): ModificationNode(token) {}

std::string ProjectionNode::translate(vector<std::string> &v) {
    std::string output = "SELECT ";
    for (auto child: children) {
        output += child->translate();
    }
    if (!v[1].empty()) {
        createView(v);
        v[2] = lastTable;
    }
    std::string tempTableName = "TempTable" + to_string(tempTableNumber++);
    lastTable = tempTableName;
    std::string tempTable = " AS " + tempTableName;
    output += " FROM ";
    if (!v[3].empty() && !v[1].empty()) { // Add brackets when selecting from a query
        tempTable = ")" + tempTable;
        output += "(";
    }
    v[3] = tempTable + v[3];
    v[1].insert(v[1].begin(), output.begin(), output.end());
    return "";
}

TableNode::TableNode(const string &token): TreeNode(token) {}

std::string TableNode::translate(vector<std::string> &v) {
    v[2] += translate();
    return "";
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

RenameNode::RenameNode(const string &token): ModificationNode(token) {}

std::string RenameNode::translate(vector<std::string> &v) {
    std::string output;
    // Check if it's only a table
    std::string table;
    if (!v[2].empty() && v[1].empty()) {
        table = v[2];
        for (int i = 1; i < v.size(); ++i) {
            v[i].clear();
        }
    } else {
        createView(v);
//        std::string tempTable = "TempTable" + to_string(tempTableNumber++);
//        for (int i = 1; i < v.size(); ++i) {
//            output += v[i]; // Write the string
//            v[i].clear(); // Empty the string
//        }
//        v[0] += "CREATE VIEW " + tempTable + " AS (" + output + ");\n";
//        output.clear();
//        lastTable = tempTable;
        table = lastTable;
    }
    std::string rename = (*children.crbegin())->translate();
    // Parse the name
    std::string newTable = rename.substr(3);
    // Parse the type
    rename = rename.substr(0, 3);
    // If the table has to be renamed, rename it
    std::string type;
    std::string old;
    std::string s = newTable;
    if (rename == "COL") {
        type = "COLUMN ";
        // Parse old and new name
        int separator = newTable.find(',');
        old = newTable.substr(separator + 1) + " ";
        newTable = newTable.substr(0, separator);
        s = table;
    }
    // Write the string
    v[0] += "ALTER TABLE " + table + " RENAME " + type + old + "TO " + newTable;
    lastTable = s;

    v[0] += output + ";\n";
    v[2] = lastTable;
    return "";
}

RenamePremiseNode::RenamePremiseNode(const string &token): TreeNode(token) {}

std::string RenamePremiseNode::translate() const {
    // Table rename
    if (children.size() == 1) {
        return "TAB" + children[0]->translate();
    }
    std::string direction = children[1]->getToken();
    std::string table = children[0]->translate();
    if (direction == "RIGHT_ARROW") {
        table = children[2]->translate() + "," + table;
    } else {
        table += "," + children[2]->translate();
    }
    return "COL" + table;
}
