//
// Created by robnoo on 3/01/22.
//

#ifndef RATSQL_PARSING_TREENODE_H
#define RATSQL_PARSING_TREENODE_H


#include "ParseTemplate.h"
#include <vector>

class TreeNode {
public:
    /**
     * @brief TreeNode parameter constructor
     * @param token the token identifier this tree contains
     */
    explicit TreeNode(std::string token);
    /**
     * @brief TreeNode destructor
     */
    ~TreeNode();

    /**
     * @brief Adds a child to the tree
     * @param tree tree to add as a child
     */
    void addChild(TreeNode* tree);
    /**
     * @brief Returns the child at the given index
     * @param index index of the requested child
     * @return pointer to the child at the given position
     */
    TreeNode* getChild(int index);
    /**
     * @brief Returns a vector of the children of the tree
     * @return vector of pointers to the children
     */
    [[nodiscard]] const std::vector<TreeNode*> &getChildren() const;

    /**
     * @brief Assigns tokens based onthe given tokens and the index
     * @param tokens tokens to be assigned
     * @param tokenIndex index at which the tokens should be assigned
     */
    void assignTokens(const std::vector<ParseToken> &tokens, int &tokenIndex);

    /**
     * @brief Exports the current tree to the given file
     * @param file file to export the dot graph to
     */
    void exportDot(std::string& file);
    /**
     * @brief Exports the children of the tree
     * @param out file to write the tree to
     * @param index current index that belongs to the tree
     */
    void exportDotRecursive(std::ofstream& out, int& index);

    /**
     * @brief Function for translating a node
     * @return string representation of the node's contents
     */
    [[nodiscard]] virtual std::string translate() const;

    /**
     * @brief Function to insert the translation of a node into an vector
     * @param v vector to put the translation in
     */
    virtual std::string translate(std::vector<std::string> &v) {return "";};

    /**
     * @brief Getter for the token
     * @return the token
     */
    [[nodiscard]] const string &getToken() const;

    /**
     * @brief Getter for the value
     * @return the value
     */
    [[nodiscard]] const string &getValue() const;

protected:
    /**
     * @brief Token identifier belonging to the tree
     */
    std::string token;
    /**
     * @brief Value of the token belonging to the tree
     */
    std::string value;
    /**
     * @brief Children of the tree
     */
    std::vector<TreeNode*> children;

};

class BasicNode: public TreeNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit BasicNode(const std::string &token);

    /**
     * @brief Translates the current node
     * @return translated representation
     */
    [[nodiscard]] std::string translate() const override;
};

class ValueNode: public TreeNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
     explicit ValueNode(const std::string &token);

     /**
     * @brief Translates the current node
     * @return translated representation
     */
     [[nodiscard]] std::string translate() const override;
};

class RootNode: public TreeNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit RootNode(const std::string &token);

    [[nodiscard]] std::string translate() const override;
    /**
    * @brief Translates the current node
    * @return translated representation
    */
    std::string translate(std::vector<std::string> &v) override;
};

class ExpressionNode: public TreeNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit ExpressionNode(const std::string &token);
    /**
    * @brief Translates the current node
    * @return translated representation
    */
    [[nodiscard]] std::string translate() const override;
    /**
    * @brief Translates the current node
    * @return translated representation
    */
    std::string translate(std::vector<std::string> &v) override;

    std::vector<std::string> translateToVector();

    static void createView(vector<string> &v);

    static void createView(vector<string> &v, const string &viewName);

protected:
    static unsigned int tempTableNumber;

    static std::string lastTable;
};

class JoinNode: public ExpressionNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit JoinNode(const std::string &token);

    std::string translate(std::vector<std::string> &v) override;
};

class ModificationNode: public ExpressionNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit ModificationNode(const std::string &token);
    /**
    * @brief Translates the current node
    * @return translated representation
    */
    std::string translate(std::vector<std::string> &v) override;

};

class SelectionNode: public ModificationNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit SelectionNode(const std::string &token);

    std::string translate(std::vector<std::string> &v) override;
};

class ProjectionNode: public ModificationNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit ProjectionNode(const std::string &token);

    std::string translate(std::vector<std::string> &v) override;
};

class RenameNode: public ModificationNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit RenameNode(const std::string &token);

    std::string translate(std::vector<std::string> &v) override;
};

class RenamePremiseNode: public TreeNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit RenamePremiseNode(const std::string &token);
    /**
    * @brief Translates the current node
    * @return translated representation
    */
    [[nodiscard]] std::string translate() const override;
};

class SetOperatorNode: public ExpressionNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit SetOperatorNode(const std::string &token);

    std::string translate(std::vector<std::string> &v) override;
};

class TableNode: public TreeNode {
public:
    /**
     * @brief Constructor
     * @param token token identifier for this node
     */
    explicit TableNode(const std::string &token);
    /**
    * @brief Translates the current node
    * @return translated representation
    */
    [[nodiscard]] std::string translate() const override;
    /**
    * @brief Translates the current node
    * @return translated representation
    */
    std::string translate(std::vector<std::string> &v) override;
};



#endif //RATSQL_PARSING_TREENODE_H
