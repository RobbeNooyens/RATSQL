//
// Created by Pablo Deputter on 26/01/2022.
//

#include "RAHighLighter.h"

RAHighLighter::RAHighLighter(QTextEdit *parent) : HighLighter(parent)
{
    // Syntax highlighting for operators
    QStringList operators;
    QTextCharFormat formatOperators;
    formatOperators.setForeground(QBrush(QColor(4, 185, 127)));
    formatOperators.setFontWeight(13);
    operators << "\\π" << "\\σ" << "\\ρ" << "\\→" << "\\←" << "\\∨" << "\\¬" << "\\≠" << "\\=" << "\\=" << "\\>"
              << "\\<" << "\\≥" << "\\≤" << "\\∧"<< "\\∩" << "\\∪" << "\\/" << "\\-" << "\\⨯" << "\\⨝" << "\\{"
              << "\\}" << "\\(" << "\\)" << "\\." << "\\," << "\\'";
    addKeywords(operators, formatOperators);
}
