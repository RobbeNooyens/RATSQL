//
// Created by Maarten on 06/01/2022.
//

#include "SQLTranslator.h"

SQLTranslator::SQLTranslator(TreeNode *root): rootNode(root) {}

std::string SQLTranslator::translate() const {
    std::string output = translateNode(rootNode);
    return output;
}

std::string SQLTranslator::translateNode(TreeNode* root) {
    std::string output;
    for (auto child : root->getChildren()) {
        output += translateNode(child);
    }
    output += root->translate();
    return output;
}
