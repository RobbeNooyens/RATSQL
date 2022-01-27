//
// Created by Maarten on 27/01/2022.
//

#ifndef RATSQL_PARSING_ILLEGALENTRYEXCEPTION_H
#define RATSQL_PARSING_ILLEGALENTRYEXCEPTION_H

#include <exception>
#include <string>

class IllegalEntryException: public std::exception {
private:
    /// Message of the latest exception
    std::string message;

public:
    /**
     * @brief Constructor for an illegal entry exception
     * @param entry         Illegal entry that was given
     * @param m             Reason for the illegal entry
     */
    IllegalEntryException(const std::string &entry, const std::string &m) {
        message = "Illegal Entry: '" + entry + "' found. Reason: " + m;
    }
    /**
     * @brief   Override of the standard what function of exception
     * @return  Why the exception happened
     */
    const char * what() const noexcept override {
        return message.c_str();
    }
};

#endif //RATSQL_PARSING_ILLEGALENTRYEXCEPTION_H
