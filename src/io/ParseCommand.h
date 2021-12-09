//
// Created by robnoo on 9/12/21.
//

#ifndef RATSQL_SHUNTING_YARD_PARSECOMMAND_H
#define RATSQL_SHUNTING_YARD_PARSECOMMAND_H


#include <string>

class ParseCommand {
public:
    void operator()(std::string& command);

private:
    std::string commandName;
    std::vector<std::string> arguments;
};


#endif //RATSQL_SHUNTING_YARD_PARSECOMMAND_H
