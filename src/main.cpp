/*
 *  +---------------------------------------------------------------+
 *  |                                                               |
 *  |   RATSQL Project  -  Relational Algebra To SQL                |
 *  |                                                               |
 *  |   Contributors:   Pablo Deputter, Cédric Leclercq,            |
 *  |                   Robbe Nooyens, Maarten Peirsman             |
 *  |                                                               |
 *  |   University of Antwerp   -   Advanced Programming            |
 *  |                                                               |
 *  +---------------------------------------------------------------+
 */

#include "parser/RelaxParser.h"

#include <QApplication>
#include <QPushButton>
#include <iostream>

int main(int argc, char *argv[]) {
    RelaxParser parser = RelaxParser(argv[1]);
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
    std::cout << "Hello world\n";
}
