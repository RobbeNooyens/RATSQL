//
// Created by robnoo on 26/01/22.
//

#ifndef RATSQL_PARSING_TOKENS_H
#define RATSQL_PARSING_TOKENS_H

#include <string>

namespace Tokens {

    const std::string PI = "PI";
    const std::string SIGMA = "SIGMA";
    const std::string RHO = "RHO";

    const std::string EQUALS = "EQ";
    const std::string NOT_EQUALS = "NEQ";
    const std::string GREATER_THAN_OR_EQUALS = "GEQ";
    const std::string LESS_THAN_OR_EQUALS = "LEQ";
    const std::string LESS_THAN = "LT";
    const std::string GREATER_THAN = "GT";

    const std::string AND = "AND";
    const std::string OR = "OR";
    const std::string NOT = "NOT";


    const std::string INTERSECT = "INTERSECT";
    const std::string UNION = "UNION";
    const std::string DIVIDE = "DIV";
    const std::string SUBTRACT = "SUB";

    const std::string JOIN = "JOIN";
    const std::string SCALAR = "SCALAR";

    const std::string ROUNDED_BRACKET_LEFT = "ROUNDED_BRACKET_LEFT";
    const std::string ROUNDED_BRACKET_RIGHT = "ROUNDED_BRACKET_RIGHT";

    const std::string ARROW_LEFT = "LEFT_ARROW";
    const std::string ARROW_RIGHT = "RIGHT_ARROW";

    const std::string END_OF_LINE = "EOL";
    const std::string COMMA = "COMMA";
    const std::string DOT = ".";

    const std::string MULTI_COMMENT_START = "MULTI_COMMENT_START";
    const std::string MULTI_COMMENT_END = "MULTI_COMMENT_END";
    const std::string LINE_COMMENT_START = "LINE_COMMENT_START";

    const std::string NAME = "NAME";
    const std::string DIGIT = "DIGIT";
    const std::string QUOTE = "QUOTE";

    const std::string SUBSTITUTION = "SUBSTITUTION";
}

#endif //RATSQL_PARSING_TOKENS_H
