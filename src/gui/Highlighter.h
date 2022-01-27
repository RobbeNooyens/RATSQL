//
// Created by Pablo Deputter on 07/01/2022.
//

#ifndef RATSQL_PARSING_HIGHLIGHTER_H
#define RATSQL_PARSING_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextEdit>
#include <QRegularExpression>

#include <iostream>

#include "../algorithms/LevenshteinDistance.h"

/**
 * @brief Class for QTextEdit syntax highlighter, derived from QSyntaxHighlighter
 */
class HighLighter : public QSyntaxHighlighter
{
Q_OBJECT
private:
    /**
     * @brief Struct for SyntaxHighlighter rule
     */
    struct Rule
    {
        QRegularExpression mRe; /**< QRegularExpression - regex of rule to find keyword */
        QTextCharFormat mFormat; /**< QTextCharFormat - format of rule to highlight/color keyword */
    };
    std::vector<Rule> mRules; /**< std::vector<Rule> - std::vector containing all highlight rules */
    int mDeviation;
    bool mErrorDetection;
    bool mErrorFlag;
public:
    /**
     * @brief Constructor for Highlighter object
     * @param parent QTextEdit - pointer to parent widget
     */
    explicit HighLighter(QTextEdit *parent = nullptr);
    /**
     * @brief Add keywords to be highlighted in given format
     * @param keywords QStringList - list containing keywords
     * @param format QTextCharFormat - format of keywords
     */
    void addKeywords(const QStringList& keywords, const QTextCharFormat& format);

    void setErrorDetection(bool b) { mErrorDetection = b; }
    void setDeviation(int dev) { mDeviation = dev; }
protected:
    /**
     * @brief Called every time whenever a update happens in the connected QTextEdit class / parent class and shall
     *        highlight given text
     * @param text QString - text inside QTextEdit class
     */
    void highlightBlock(const QString &text) override;

private slots:
    void onSpacePressed() { mErrorFlag = !mErrorFlag; };
};


#endif //RATSQL_PARSING_HIGHLIGHTER_H
