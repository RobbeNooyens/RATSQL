#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QObject>
#include <QCompleter>
#include <QSyntaxHighlighter>

#include <iostream>
#include <map>

#include "../algorithms/LevenshteinDistance.h"

class HighLighter : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    std::map<QString, bool> mBuffer;

public:
    HighLighter(QTextEdit *parent) :QSyntaxHighlighter(parent) {}

protected:
    virtual void highlightBlock(const QString &text) override;
};

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit(QWidget* parent = nullptr);

    ~TextEdit()
    {
        // TODO
    }

protected:

private:
    QString getSelectedText() const;

private slots:

    /**
     * @brief
     * @param character
     */
    void onCharacterAdded(QString character) { insertPlainText(character); }

    void onCustomMenu(QPoint);
    void onCorrect(QAction * act);

    void onErrorDetection(bool b) { mErrorDetection = b; }
    void onOptimize(bool b) { mOptimize = b; }
    void onNamingConventions(bool b) { mNamingConventions = b; }

private:

    HighLighter* mHighlighter;


    bool mErrorDetection;
    bool mOptimize;
    bool mNamingConventions;
};

#endif // TEXTEDIT_H
