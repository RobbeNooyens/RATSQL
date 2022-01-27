//
// Created by Maarten on 06/01/2022.
//

#ifndef RATSQL_PARSING_SQLTRANSLATOR_H
#define RATSQL_PARSING_SQLTRANSLATOR_H

#include "TreeNode.h"

/**
 * @class SQLTranslator
 */
class SQLTranslator {
    /// @brief Rootnode of the parse tree
    TreeNode* rootNode;

public:
    /**
     * @brief Constructor
     * @param root rootnode of the parse tree
     */
    explicit SQLTranslator(TreeNode* root);

    /**
     * @brief Translate to SQL
     * @return
     */
    [[nodiscard]] std::string translate() const;

    /**
     * @brief Function that translates a tree using postorder traversal
     * @param root root of the tree
     * @return string containing the translation
     */
    static string translateNode(TreeNode *root);
};


#endif //RATSQL_PARSING_SQLTRANSLATOR_H
