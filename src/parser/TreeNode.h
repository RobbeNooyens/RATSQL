//
// Created by robnoo on 3/01/22.
//

#ifndef RATSQL_PARSING_TREENODE_H
#define RATSQL_PARSING_TREENODE_H


#include "ParseTemplate.h"
#include <vector>

class TreeNode {
public:
    explicit TreeNode(std::string token);
    ~TreeNode();

    void addChild(TreeNode* tree);
    TreeNode* getChild(int index);
    const std::vector<TreeNode*> &getChildren() const;

    void assignTokens(const std::vector<ParseToken> &tokens, int &tokenIndex);

    void exportDot(std::string& file);
    void exportDotRecursive(std::ofstream& out, int& index);

    /**
     * Function for translating a node
     * @return string representation of the node's contents
     */
    virtual std::string translate() const;

    /**
     * Function to insert the translation of a node into an vector
     * @param v vector to put the translation in
     */
    virtual void translate(std::vector<std::string> &v) const {};

    /**
     * Getter for the token
     * @return the token
     */
    const string &getToken() const;

    /**
     * Getter for the value
     * @return the value
     */
    const string &getValue() const;

protected:
    std::string token;
    std::string value;
    std::vector<TreeNode*> children;

};

class BasicNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit BasicNode(const std::string &token);

    std::string translate() const override;
};

class ValueNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
     explicit ValueNode(const std::string &token);

     std::string translate() const override;
};

class ExpressionNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit ExpressionNode(const std::string &token);

    std::string translate() const override;

    void translate(std::vector<std::string> &v) const override;
};

class ModificationNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit ModificationNode(const std::string &token);

    void translate(std::vector<std::string> &v) const override;
};

class SelectionNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit SelectionNode(const std::string &token);

    void translate(std::vector<std::string> &v) const override;
};

class ProjectionNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit ProjectionNode(const std::string &token);

    void translate(std::vector<std::string> &v) const override;
};

class RenameNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit RenameNode(const std::string &token);
};

class TableNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit TableNode(const std::string &token);

    std::string translate() const override;

    void translate(std::vector<std::string> &v) const override;
};



#endif //RATSQL_PARSING_TREENODE_H
