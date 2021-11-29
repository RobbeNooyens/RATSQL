#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "algorithms/LevenshteinDistance.h"

int main(int argc, char *argv[]) {

    std::cout << std::boolalpha << LevenshteinDistance::evalLevenshteinDistance("ikCEDRICbencoolenjijniet",
                                                                                "ikbencoolenjijniet", 6) << "\n";

//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    return 69;
    //return QApplication::exec();
    std::cout << "Hello world\n";
}
