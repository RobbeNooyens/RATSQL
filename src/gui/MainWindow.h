/**
 *  ╒═══════════════════════════════════════════════════════════╕
 *  │                                                           │
 *  │                     RATSQL Project                        │
 *  │                Relational Algebra To SQL                  │
 *  │                                                           │
 *  │       Contributors: Pablo Deputter, Cédric Leclercq,      │
 *  │                     Robbe Nooyens, Maarten Peirsman       │
 *  │                                                           │
 *  │    University of Antwerp - Machines en Berekenbaarheid    │
 *  │                                                           │
 *  ╘═══════════════════════════════════════════════════════════╛
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStringListModel>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QValidator>
#include <QString>
#include <QRegularExpression>
#include <QFileDialog>
#include <QPixmap>

#include "CharButton.h"
#include "SettingButton.h"
#include "TextEdit.h"
#include "../system/System.h"

#include <memory>
#include <vector>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Main Window of GUI
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for MainWindow object
     * @param parent QWidget - pointer to parent
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
    void init();
    /**
     * @brief Create menu's
     */
    void createMenu();
    /**
     * @brief Create actions
     */
    void createAction();
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
    /**
     * @brief Executed when convertButton is triggered
     */
    void onConvertBtnClicked();
    /**
     * @brief Triggered when About action is triggered
     */
    void onAboutAct();
    /**
    * @brief Triggered when Save action is triggered
    */
    void onSaveAct();
    /**
    * @brief Triggered when Open action is triggered
    */
    void onOpenAct();
private:
    Ui::MainWindow *ui;
    /// std::vector<CharButton*> - vector containing special symbol buttons
    std::vector<CharButton*> mCharacters;
    /// std::vector<CharButton*> - vector containing setting buttons
    std::vector<QWidget*> mSettings;
    /// System - pointer to system to execute parser functions and translate RA query to SQL
    std::unique_ptr<System> mSys;
    TextEdit* mTextEdit;
    TextEdit* mOutputTextEdit;
    // Menu's
    QMenu* mAbout;
    QMenu* mFile;
    // Actions
    QAction* mAboutAct;
    QAction* mSaveAct;
    QAction* mOpenAct;
};
#endif // MAINWINDOW_H
