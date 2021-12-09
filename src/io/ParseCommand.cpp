//
// Created by robnoo on 9/12/21.
//

#include <vector>
#include "ParseCommand.h"

using namespace std;

void split(const string& input, string& cmdName, vector<string>& args){
    args.clear();
    bool isName = true;
    std::string word;
    for(char c: input) {
        if(c == ' ') {
            if(isName) {
                cmdName = word;
                isName = false;
            } else {
                args.push_back(word);
            }
            word = "";
        } else {
            word.push_back(c);
        }
    }
}

void ParseCommand::operator()(std::string &command) {
    split(command, commandName, arguments);
    if(commandName.empty())
        return;

    // TODO: Decide what to to

    if(command == "command1") {

    } else if(command == "command2") {

    }
}

