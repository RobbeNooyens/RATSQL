#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStringListModel>
#include <QMessageBox>

#include "CharButton.h"
#include "SettingButton.h"
#include "TextEdit.h"

#include <memory>
#include <vector>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for MainWindow object
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @Destructor for MainWindow object
    */
    ~MainWindow();
private:
    /**
     * @brief Create buttons, actions, ...
     */
    void createMenu();
    /**
     * @brief Create buttons for different special characters
     */
    void createCharButtons();
    /**
     * @brief Create check buttons for the converting settings
     */
    void createSettingButtons();
    /**
     * @brief Show message box on screen
     * @param icon QMessageBox::Icon - icon of messageBox
     * @param title QString - title of messageBox
     * @param text QString - text of messageBox
     * @param button QMessageBox::StandardButton - standard button on messagebox
     * @return QMessageBox - newly created messageBox with given specs
     */
    QMessageBox* createMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text,
                                  QMessageBox::StandardButton button);
public slots:
    void onConvertBtnClicked();

private:
    Ui::MainWindow *ui;
    std::vector<CharButton*> mCharacters;
    std::vector<SettingButton*> mSettings;

    TextEdit* mTextEdit;
};
#endif // MAINWINDOW_H
