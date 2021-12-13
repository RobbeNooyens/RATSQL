/**
 *  ╒══════════════════════════════════════════════════╕
 *  │                                                  │
 *  │                 RATSQL Project                   │
 *  │            Relational Algebra To SQL             │
 *  │                                                  │
 *  │  Contributors: Pablo Deputter, Cédric Leclercq,  │
 *  │               Robbe Nooyens, Maarten Peirsman    │
 *  │                                                  │
 *  │   University of Antwerp - Advanced Programming   │
 *  │                                                  │
 *  ╘══════════════════════════════════════════════════╛
 */

#ifndef RATSQL_SHUNTING_YARD_MAINWINDOW_H
#define RATSQL_SHUNTING_YARD_MAINWINDOW_H


#include <QMainWindow>

class GUIHandler;

class MainWindow: public QMainWindow {
public:
    MainWindow();

    // TODO: implement gui classes

private:
    // Attributes
    std::shared_ptr<GUIHandler> guiHandler;

};


#endif //RATSQL_SHUNTING_YARD_MAINWINDOW_H
