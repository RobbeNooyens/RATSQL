//
// Created by Pablo Deputter on 26/01/2022.
//

#ifndef RATSQL_PARSING_RAHIGHLIGHTER_H
#define RATSQL_PARSING_RAHIGHLIGHTER_H

#include "Highlighter.h"

class RAHighLighter : public HighLighter {

public:
    /**
     * @brief Constructor for RAHighLighter object
     * @param parent QTextEdit - pointer to parent widget
     */
    explicit RAHighLighter(QTextEdit *parent = nullptr);
};


#endif //RATSQL_PARSING_RAHIGHLIGHTER_H
