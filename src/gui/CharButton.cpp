#include "CharButton.h"

CharButton::CharButton(QString character, QWidget* parent)
{
    mChar = character;
    setFixedSize(35, 35);
    setText(character);
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}
