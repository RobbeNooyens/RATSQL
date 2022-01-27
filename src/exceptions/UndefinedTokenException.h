//
// Created by Maarten on 13/12/2021.
//

#ifndef RATSQL_UNDEFINEDTOKENEXCEPTION_H
#define RATSQL_UNDEFINEDTOKENEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

/**
 * @class UndefinedTokenException
 */
class UndefinedTokenException: public exception {
    /// @brief Message of the exception
    string message;
public:
    /**
     * @brief Constructor for UndefinedTokenException
     * @param m message for the error
     */
    explicit UndefinedTokenException(const string &m) {
        message = "We couldn't find a token for entry: '" + m + "'. Consider checking for typo's.";
    }

    /**
     * @brief Function that returns more information about the error that occured
     * @return string explaining what went wrong
     */
    const char * what() const noexcept override;
};

const char *UndefinedTokenException::what() const noexcept {
    return message.c_str();
}

#endif //RATSQL_UNDEFINEDTOKENEXCEPTION_H
