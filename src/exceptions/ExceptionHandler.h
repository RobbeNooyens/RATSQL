//
// Created by Cédric Leclercq on 20/12/2021.
//

#ifndef RATSQL_SHUNTING_YARD_EXCEPTIONHANDLER_H
#define RATSQL_SHUNTING_YARD_EXCEPTIONHANDLER_H

#include <string>

class ExceptionHandler {
public:
    __attribute__((unused)) static ExceptionHandler& getInstance();
    static void handle(std::exception& exc, const std::string& message) noexcept;
};


#endif //RATSQL_SHUNTING_YARD_EXCEPTIONHANDLER_H
