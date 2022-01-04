#include "SettingButton.h"

SettingButton::SettingButton(QString name, QWidget* parent)
{
    setText(name);
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}
