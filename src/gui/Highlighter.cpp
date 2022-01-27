//
// Created by Pablo Deputter on 07/01/2022.
//

#include "Highlighter.h"

HighLighter::HighLighter(QTextEdit *parent) : QSyntaxHighlighter(parent), mErrorDetection(false), mDeviation(1), mErrorFlag(false) {}

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
}
