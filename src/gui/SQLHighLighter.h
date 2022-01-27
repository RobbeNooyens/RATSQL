//
// Created by Pablo Deputter on 26/01/2022.
//

#ifndef RATSQL_PARSING_SQLHIGHLIGHTER_H
#define RATSQL_PARSING_SQLHIGHLIGHTER_H

#include "Highlighter.h"

class SQLHighLighter : public HighLighter {

public:
    /**
     * @brief Constructor for SQLHighLighter object
     * @param parent QTextEdit - pointer to parent widget
     */
    explicit SQLHighLighter(QTextEdit *parent = nullptr);
};


#endif //RATSQL_PARSING_SQLHIGHLIGHTER_H
