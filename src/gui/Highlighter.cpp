//
// Created by Pablo Deputter on 07/01/2022.
//

#include "Highlighter.h"

HighLighter::HighLighter(QTextEdit *parent) : QSyntaxHighlighter(parent), mErrorDetection(false), mDeviation(1), mErrorFlag(false)
{
    // Syntax highlighting for operators
    QStringList operators;
    QTextCharFormat formatOperators;
    formatOperators.setForeground(QBrush(QColor(4, 185, 127)));
    formatOperators.setFontWeight(13);
    operators << "\\π" << "\\σ" << "\\ρ" << "\\->" << "\\<-" << "\\∨" << "\\¬" << "\\≠" << "\\=" << "\\=" << "\\>"
             << "\\<" << "\\≥" << "\\≤" << "\\∧"<< "\\∩" << "\\∪" << "\\/" << "\\-" << "\\⨯" << "\\⨝" << "\\{"
             << "\\}" << "\\(" << "\\)" << "\\." << "\\," << "\\'";
    addKeywords(operators, formatOperators);
}

void HighLighter::addKeywords(const QStringList &keywords, const QTextCharFormat& format)
{
    for (const auto& i : keywords)
    {
        Rule newRule{QRegularExpression(i), format};
        mRules.emplace_back(newRule);
    }
}

void HighLighter::highlightBlock(const QString &text)
{
    for (const auto &i : mRules)
    {
        QRegularExpressionMatchIterator it = i.mRe.globalMatch(text);
        while (it.hasNext())
        {
            QRegularExpressionMatch next = it.next();
            setFormat((int) next.capturedStart(), (int) next.capturedLength(), i.mFormat);
        }
    }

    // TODO - nog steeds te traag en heeft eig ook geen zin om te doen

//    if (!mErrorDetection || !mErrorFlag) { return; }
//
//    QTextCharFormat formatError;
//    formatError.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
//    formatError.setUnderlineColor(QColor(255, 0, 0));
//    QStringList list = text.split(QRegularExpression(R"((\s|\n|\r)+)"));
//
//    int counter = 0;
//    int pointer = 1;
//    for (const auto &i : list)
//    {
//        QString word = text.section(QRegularExpression("\\s+"), counter, counter,
//                                    QString::SectionSkipEmpty).toLower();
//        const auto& suggestions = LevenshteinDistance::getInstance().eval(word.toStdString(), mDeviation);
//        if (!suggestions.first)
//        {
//            setFormat(pointer, (int) word.length(), formatError);
//        }
//        pointer += (int) word.length();
//        counter++;
//    }
}
