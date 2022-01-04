#ifndef CHARBUTTON_H
#define CHARBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QVariantAnimation>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QColor>

#include <string>

class CharButton : public QPushButton
{
    Q_OBJECT
private:
    QString mChar; /**< QString - special character / symbol that button holds */
public:
    /**
     * @brief Constructor for CharButton object
     * @param character QString - special character
     * @param parent - QWiqdget - pointer to parent to send signals to
     */
    CharButton(QString character, QWidget *parent = nullptr);
signals:
    /**
     * @brief Clicked signal
     * @param character QString - sent character
     */
    void clicked(QString character);
private slots:
    /**
     * @brief Emit signal when clicked on CharButton
     */
    void reemitClicked() { emit clicked(mChar); }
};


#endif // CHARBUTTON_H
