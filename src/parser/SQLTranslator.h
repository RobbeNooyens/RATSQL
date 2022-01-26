//
// Created by Maarten on 06/01/2022.
//

#ifndef RATSQL_PARSING_SQLTRANSLATOR_H
#define RATSQL_PARSING_SQLTRANSLATOR_H

#include "TreeNode.h"

class SQLTranslator {
    /// Rootnode of the parse tree
    TreeNode* rootNode;

public:
    /**
     * Constructor
     * @param root rootnode of the parse tree
     */
    explicit SQLTranslator(TreeNode* root);

    /**
     *
     * @return
     */
    std::string translate() const;

    /**
     * Function that translates a tree using postorder traversal
     * @param root root of the tree
     * @return string containing the translation
     */
    static string translateNode(TreeNode *root);
};


#endif //RATSQL_PARSING_SQLTRANSLATOR_H
