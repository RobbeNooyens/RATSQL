//
// Created by Maarten on 13/12/2021.
//

#ifndef RATSQL_UNDEFINEDTOKENEXCEPTION_H
#define RATSQL_UNDEFINEDTOKENEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class UndefinedTokenException: public exception {
    string message;

public:
    /**
     * Constructor for UndefinedTokenException
     * @param m message for the error
     */
    UndefinedTokenException(const string &m) {
        message = "We couldn't find a token for entry: '" + m + "'. Consider checking for typo's.";
    }

    /**
     * Functiont that returns more information about the error that occured
     * @return string explaining what went wrong
     */
    const char * what() const noexcept override;
};

#endif //RATSQL_UNDEFINEDTOKENEXCEPTION_H
