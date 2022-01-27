//
// Created by robnoo on 3/01/22.
//

#ifndef RATSQL_PARSING_PARSESTATE_H
#define RATSQL_PARSING_PARSESTATE_H


#include <string>
#include <vector>
#include <memory>
#include "../datastructures/CFG.h"

class TreeNode;

/**
 * @brief Reperesent a parse state for the Earley Parser
 */
class ParseState {
public:
    /**
     * @brief Parameter constructor
     * @param production production that this state uses
     * @param dot dot indicating where we are in the production
     * @param origin origin from which we started scanning
     */
    ParseState(ProductionRule production, unsigned int dot, unsigned int origin);

    /**
     * @return the production rule that belongs to this parsestate
     */
    const ProductionRule& getProduction();
    /**
     * @return the position of the dot in the productionrule
     */
    [[nodiscard]] unsigned int getDot() const;
    /**
     * @return the origin from which we started scanning
     */
    [[nodiscard]] unsigned int getOrigin() const;
    /**
     * @return the next element after the dot in the production
     */
    const std::string& nextElement();
    /**
     * @return states derived from this parsestate, used to call back and construct the tree
     */
    std::vector<std::pair<ParseState*, ParseState*>>& getDerivedStates();
    /**
     * @return true if the dot is behind the last production element
     */
    bool isFinished();
    /**
     * @return string representation of this parse state
     */
    std::string toString();

    // Actions
    /**
     * @brief Adds a derived state
     * @param state state to add to these derived states
     */
    void addDerivedState(std::pair<ParseState*, ParseState*> state);
    /**
     * @brief Constructs the parse tree
     * @param tree to be used to evaluate this parse state
     */
    void evaluate(TreeNode *tree);

    // Comparators
    /**
     * @brief Equals operator overloader
     * @param rhs other state
     * @return true if this and the rhs ParseState are considered equal
     */
    bool operator==(ParseState& rhs);
    /**
     * @brief Not equals operator overloader
     * @param rhs ParseState to compare with
     * @return true if this and the other state are not considered equal
     */
    bool operator!=(ParseState& rhs);

private:
    /**
     * @brief Represents the production
     */
    ProductionRule production;
    /**
     * @brief represents the dot position
     */
    unsigned int dot = 0;
    /**
     * @brief Represents the origin position which we started scanning from
     */
    unsigned int origin = 0;
    /**
     * @brief Contains the derived states belonging to this state
     */
    std::vector<std::pair<ParseState*, ParseState*>> derivedStates;

    /**
     * @brief Creates a TreeNode
     * @param s treenode identifier
     * @return TreeNode pointer
     */
    TreeNode *createNode(const std::string &s) const;
};


#endif //RATSQL_PARSING_PARSESTATE_H
