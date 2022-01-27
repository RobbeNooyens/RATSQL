//
// Created by Cédric Leclercq on 26/01/2022.
//

#include "System.h"
#include "../utilities/Parsers.h"
#include "../datastructures/RAExpression.h"

std::string System::convertToSQL(string query) {
    std::shared_ptr<RAExpression> expression = parsers::toRelationalExpression(query);



    return {};
}
