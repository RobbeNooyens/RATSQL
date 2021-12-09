//
// Created by robnoo on 9/12/21.
//

#ifndef RATSQL_SHUNTING_YARD_PARSESETTINGS_H
#define RATSQL_SHUNTING_YARD_PARSESETTINGS_H


struct ParseSettings {
    ParseSettings(bool autocorrect, bool optimizeQuery): autocorrect(autocorrect), optimizeQuery(optimizeQuery) {};
    bool autocorrect = false;
    bool optimizeQuery = false;
};


#endif //RATSQL_SHUNTING_YARD_PARSESETTINGS_H
