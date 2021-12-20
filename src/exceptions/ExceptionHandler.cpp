//
// Created by Cédric Leclercq on 20/12/2021.
//

#include "ExceptionHandler.h"
#include <iostream>


__attribute__((unused)) ExceptionHandler &ExceptionHandler::getInstance() {
    static ExceptionHandler excHandler;
    return excHandler;
}

void ExceptionHandler::handle(std::exception &exc, const std::string& message) {
    std::cerr << message << std::endl;
    std::cout << "The exception was: ";
    std::cerr << exc.what() << std::endl;
}

