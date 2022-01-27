//
// Created by Cédric Leclercq on 20/12/2021.
//

#ifndef RATSQL_SHUNTING_YARD_EXCEPTIONHANDLER_H
#define RATSQL_SHUNTING_YARD_EXCEPTIONHANDLER_H

#include <string>

class ExceptionHandler {
public:
    /**
     * @brief Singleton design pattern - not used
     * @return      static instance of a exception handler object
     */
    __attribute__((unused)) static ExceptionHandler& getInstance();
    /**
     * @brief Static function to handle an exception and give an error message
     * @param exc       Exception that was thrown
     * @param message   Message to give when an exception happened
     */
    static void handle(std::exception& exc, const std::string& message) noexcept;
};


#endif //RATSQL_SHUNTING_YARD_EXCEPTIONHANDLER_H
