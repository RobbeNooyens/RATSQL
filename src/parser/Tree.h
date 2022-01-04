//
// Created by robnoo on 3/01/22.
//

#ifndef RATSQL_PARSING_TREE_H
#define RATSQL_PARSING_TREE_H


#include "ParseTemplate.h"

class Tree {
public:
    explicit Tree(std::string token);
    ~Tree();

    void addChild(Tree* tree);
    Tree* getChild(int index);

    void assignTokens(const std::vector<ParseToken> &tokens, int &tokenIndex);

    void exportDot(std::string& file);
    void exportDotRecursive(std::ofstream& out, int& index);
private:
    std::string token;
    std::string value;
    std::vector<Tree*> children;

};


#endif //RATSQL_PARSING_TREE_H
