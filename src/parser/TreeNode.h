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
    virtual std::string translate(std::vector<std::string> &v) {return "";};

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

    virtual std::string translate(std::vector<std::string> &v) override;

    void createView(vector<string> &v);

protected:
    static unsigned int tempTableNumber;

    static std::string lastTable;
};

class ModificationNode: public ExpressionNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit ModificationNode(const std::string &token);

    virtual std::string translate(std::vector<std::string> &v) override;

};

class SelectionNode: public ModificationNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit SelectionNode(const std::string &token);

    std::string translate(std::vector<std::string> &v) override;
};

class ProjectionNode: public ModificationNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit ProjectionNode(const std::string &token);

    std::string translate(std::vector<std::string> &v) override;
};

class RenameNode: public ModificationNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit RenameNode(const std::string &token);

    std::string translate(std::vector<std::string> &v) override;
};

class RenamePremiseNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit RenamePremiseNode(const std::string &token);

    std::string translate() const override;
};

class TableNode: public TreeNode {
public:
    /**
     * Constructor
     * @param token
     */
    explicit TableNode(const std::string &token);

    std::string translate() const override;

    std::string translate(std::vector<std::string> &v) override;
};



#endif //RATSQL_PARSING_TREENODE_H
