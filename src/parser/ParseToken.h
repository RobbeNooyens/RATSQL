//
// Created by robnoo on 4/01/22.
//

#ifndef RATSQL_PARSING_PARSETOKEN_H
#define RATSQL_PARSING_PARSETOKEN_H


#include <string>

class ParseToken {
public:
    explicit ParseToken(std::string content);
    ParseToken(std::string token, std::string content);

    const std::string & getToken() const;
    const std::string & getContent() const;

    ParseToken& operator=(const ParseToken &token);

private:
    std::string token;
    std::string content;

};


#endif //RATSQL_PARSING_PARSETOKEN_H
