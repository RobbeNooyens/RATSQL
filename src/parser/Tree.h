//
// Created by robnoo on 3/01/22.
//

#ifndef RATSQL_PARSING_TREE_H
#define RATSQL_PARSING_TREE_H


class Tree {
public:
    Tree(std::string content);

//    void addChild(int option, Tree* tree);
//    Tree* getChild(int option, int index);
    void addChild(Tree* tree);
    Tree* getChild(int index);

    std::vector<Tree*>& getChildren();

    ~Tree();


private:
    std::string content;
//    std::vector<std::vector<Tree*>> children;
    std::vector<Tree*> children;

};


#endif //RATSQL_PARSING_TREE_H
