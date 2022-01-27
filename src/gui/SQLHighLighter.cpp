//
// Created by Pablo Deputter on 26/01/2022.
//

#include "SQLHighLighter.h"

SQLHighLighter::SQLHighLighter(QTextEdit *parent) : HighLighter(parent)
{
    // Syntax operators
    QStringList operators;
    QTextCharFormat formatOperators;
    formatOperators.setForeground(QBrush(QColor(4, 185, 127)));
    formatOperators.setFontWeight(13);

    operators << "\\b(SELECT)\\b" << "\\b(FROM)\\b" << "\\b(WHERE)\\b" << "\\b(UNION)\\b" << "\\b(EXCEPT)\\b" << "\\b(INTERSECT)\\b"
              << "\\b(NATURAL JOIN)\\b" << "\\b(JOIN)\\b";
    addKeywords(operators, formatOperators);

    // Misc operators
    QStringList misc;
    QTextCharFormat formatMisc;
    formatMisc.setForeground(QBrush(QColor(230, 100, 10)));
    formatMisc.setFontWeight(13);

    misc << "\\*" << "\\(" << "\\)" << "\\;" << "\\≠" << "\\=" << "\\=" << "\\>" << "\\<" << "\\≥" << "\\≤";
    addKeywords(misc, formatMisc);
}
