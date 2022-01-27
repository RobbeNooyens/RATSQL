#ifndef SETTINGBUTTON_H
#define SETTINGBUTTON_H

#include <QCheckBox>
#include <QObject>

#include <iostream>

class SettingButton : public QCheckBox
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for SettingButton object
     * @param name QString - text of button
     * @param parent QWidget - pointer to parent to send signals to
     */
    SettingButton(QString name, QWidget *parent = nullptr);
signals:
    /**
     * @brief Clicked signal
     * @param flag bool - button is checked if true
     */
    void clicked(bool flag);
private slots:
    /**
     * @brief Emit signal when clicked on SettingButton
     */
    void reemitClicked() { emit clicked(isChecked()); }
};

#endif // SETTINGBUTTON_H
