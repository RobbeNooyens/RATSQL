#include "TextEdit.h"

#include <QKeyEvent>
#include <QAbstractItemView>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <QDebug>
#include <QMenu>
#include <QThread>
#include <QList>

#include <iostream>

void HighLighter::highlightBlock(const QString &text)
{
    QTextCharFormat spellingFormat;
    spellingFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
    spellingFormat.setUnderlineColor(Qt::red);

    // TODO - syntax highlighting in output
    // TODO - ingore special characters

    QStringList list = text.split(QRegularExpression("\\s++"));
    int words = list.size();
    int wordPointer = 0;
    for (int i = 0; i < words; i++)
    {
        QString section = text.section(QRegularExpression("\\s+"), i, i, QString::SectionIncludeLeadingSep);

//        // TODO - clear
//        const auto& found = mBuffer.find(section);
//        if (found != std::end(mBuffer))
//        {
//            if (found->second) { setFormat(wordPointer, section.length(), spellingFormat); }
////            else { wordPointer += section.length(); }
//            continue;
//        }

        const auto& suggestions = LevenshteinDistance::getInstance().eval(section.toStdString());
        bool correctFlag = suggestions.first;

        if (!correctFlag)
        {
            setFormat(wordPointer, section.length(), spellingFormat);
        }
        wordPointer += section.length();
        // TODO
//        mBuffer.emplace(std::make_pair(section, correctFlag));
    }
}

TextEdit::TextEdit(QWidget* parent) : QTextEdit(parent),
    mErrorDetection(false), mOptimize(false), mNamingConventions(false)
{
    setContextMenuPolicy(Qt::CustomContextMenu);

    mHighlighter = new HighLighter(this);

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomMenu(QPoint)));
}

void TextEdit::onCustomMenu(QPoint pos)
{
    QMenu* autocorrect = createStandardContextMenu();
    QMenu* customMenu = new QMenu(QString("Replace"), this);

    QTextCursor t = textCursor();
    t.select(QTextCursor::SelectionType());
    setTextCursor(t);

    if (textCursor().hasSelection())
    {
        QString selected = textCursor().selectedText();
        bool correctFlag = false;
        // TODO - distance blalalaa
        const auto& suggestions = LevenshteinDistance::getInstance().eval(selected.toStdString(), 1);

        if (!correctFlag)
        {
            QList<QAction*> newActions;
            for (const auto& i : suggestions.second)
            {
                QString data = QString::fromStdString(i);
                QAction* a = new QAction(data, customMenu);
                a->setData(data);
                newActions.push_back(a);
            }
            customMenu->addActions(newActions);
            connect(customMenu, SIGNAL(triggered(QAction*)), this, SLOT(onCorrect(QAction*)));
        }
    }
    autocorrect->insertMenu(autocorrect->actions().first(), customMenu);
    autocorrect->exec(mapToGlobal(pos));
    delete customMenu;
}

void TextEdit::onCorrect(QAction* act)
{
    if (act->data().isNull()) { return; }
    QString correction = act->data().toString();
    QTextCursor c = textCursor();
    c.beginEditBlock();
    c.removeSelectedText();
    c.insertText(correction);
    c.endEditBlock();
}

QString TextEdit::getSelectedText() const
{
    QTextCursor t = textCursor();
    t.select(QTextCursor::WordUnderCursor);
    return t.selectedText();
}
