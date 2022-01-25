#include "TextEdit.h"
#include "Highlighter.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QScrollBar>
#include <QMenu>
#include <QThread>
#include <QList>
#include <QFont>

#include <iostream>

TextEdit::TextEdit(QWidget* parent, bool readonly) : QTextEdit(parent), mErrorDetection(false), mDeviation(1),
                                      mNamingConventions(false), mOptimize(false)
{
    setFont(QFont("Courier", 12));
    setReadOnly(readonly);
    setContextMenuPolicy(Qt::CustomContextMenu);
    installEventFilter(this);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomMenu(QPoint)));

    mHighlighter = new HighLighter(this);
    connect(this, SIGNAL(spacePressed()), mHighlighter, SLOT(onSpacePressed()));
}

QMenu* TextEdit::createReplaceMenu()
{
    auto replaceMenu = new QMenu(QString("Replace"), this);
    QTextCursor t = textCursor();
    t.select(QTextCursor::SelectionType());
    setTextCursor(t);
    // If user has selected any text
    if (textCursor().hasSelection())
    {
        QString selected = textCursor().selectedText().toLower();
        const auto& suggestions = LevenshteinDistance::getInstance().eval(selected.toStdString(),
                                                                          mDeviation);

        QList<QAction*> newActions;
        for (const auto&i : suggestions.second)
        {
            QString data = QString::fromStdString(i);
            auto a = new QAction(data, replaceMenu);
            a->setData(data);
            newActions.push_back(a);
        }
        replaceMenu->addActions(newActions);
        connect(replaceMenu, SIGNAL(triggered(QAction*)), this, SLOT(onCorrect(QAction*)));
    }
    return replaceMenu;
}

bool TextEdit::eventFilter(QObject *object, QEvent *event)
{
    if (object == this && event->type() == QEvent::KeyPress)
    {
        auto* keyEvent = dynamic_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Space)
        {
            emit(spacePressed());
        }
        return false;
    }
    return false;
}

void TextEdit::onCustomMenu(const QPoint& pos)
{
    QMenu* menu = createStandardContextMenu();
    // Don't create replace sub-menu when user doesn't need error detection
    if (mErrorDetection)
    {
        const auto& replaceMenu = createReplaceMenu();
        menu->insertMenu(menu->actions().first(), replaceMenu);
    }
    menu->exec(mapToGlobal(pos));
}

void TextEdit::onCorrect(QAction* act)
{
    // User didn't select an option
    if (act->data().isNull()) { return; }
    QString suggestion = act->data().toString();
    QTextCursor c = textCursor();
    c.beginEditBlock();
    c.removeSelectedText();
    c.insertText(suggestion);
    c.endEditBlock();
}