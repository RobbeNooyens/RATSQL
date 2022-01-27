//
// Created by Maarten on 27/01/2022.
//

#ifndef RATSQL_PARSING_ILLEGALENTRYEXCEPTION_H
#define RATSQL_PARSING_ILLEGALENTRYEXCEPTION_H

#include <exception>
#include <string>

class IllegalEntryException: public std::exception {
    std::string message;

public:
    IllegalEntryException(const std::string &entry, const std::string &m) {
        message = "Illegal Entry: '" + entry + "' found. Reason: " + m;
    }

    const char * what() const noexcept override {
        return message.c_str();
    }
};

#endif //RATSQL_PARSING_ILLEGALENTRYEXCEPTION_H
