//
// Created by robnoo on 9/12/21.
//

#ifndef RATSQL_SHUNTING_YARD_RAEXPRESSION_H
#define RATSQL_SHUNTING_YARD_RAEXPRESSION_H


#include <string>

class RAExpression {
public:
    void setWord(int index, std::string);
    std::string getWord(int index);

};


#endif //RATSQL_SHUNTING_YARD_RAEXPRESSION_H
