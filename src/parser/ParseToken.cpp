//
// Created by robnoo on 4/01/22.
//

#include "ParseToken.h"

#include <utility>

ParseToken::ParseToken(std::string content): content(std::move(content)) {
    // TODO: copy functions from lexer to fill in token
}

const std::string & ParseToken::getToken() const {
    return token;
}

const std::string & ParseToken::getContent() const {
    return content;
}

ParseToken::ParseToken(std::string token, std::string content): token(std::move(token)), content(std::move(content)) {

}

ParseToken &ParseToken::operator=(const ParseToken &token) {
    this->token = token.token;
    this->content = token.content;
    return *this;
}
