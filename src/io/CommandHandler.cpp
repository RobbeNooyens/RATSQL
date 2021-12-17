/**
 *  ╒═══════════════════════════════════════════════════════════╕
 *  │                                                           │
 *  │                     RATSQL Project                        │
 *  │                Relational Algebra To SQL                  │
 *  │                                                           │
 *  │       Contributors: Pablo Deputter, Cédric Leclercq,      │
 *  │                     Robbe Nooyens, Maarten Peirsman       │
 *  │                                                           │
 *  │    University of Antwerp - Machines en Berekenbaarheid    │
 *  │                                                           │
 *  ╘═══════════════════════════════════════════════════════════╛
 */

#include <vector>
#include <iostream>
#include "CommandHandler.h"
#include "../parser/Lexer.h"

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
    if(!word.empty()) {
        if(isName) {
            cmdName = word;
        } else {
            args.push_back(word);
        }
    }
}

void CommandHandler::operator()(std::string &command) {
    split(command, commandName, arguments);
    if(commandName.empty())
        return;

    if(command == "levdis") {
        levDisCmd();
    } else if(command == "check-typos") {
        checkTypos();
    } else if(command == "autocorrect") {
        autocorrect();
    } else if(command == "load") {
        loadRA();
    } else if(command == "check-conventions") {
        checkConventions();
    } else if(command == "autoconventions") {
        autoConventions();
    } else if(command == "to-sql") {
        toSQL();
    } else if(command == "autoconventions") {
        autoConventions();
    } else if(command == "lexify") {
        lexify();
    }
}
/**
 * Command usage: levdis <word> <max levenshtein distance>
 * Preconditions: /
 * On execute: prints all words that have a max levenshtein distance from a given string
 */
void CommandHandler::levDisCmd() {
    // TODO: implement command
}

/**
 * Command usage: check-typos
 * Preconditions: RA should be loaded
 * On execute: For every replacement, print it and ask whether it should execute the replacement [Y/N]
 */
void CommandHandler::checkTypos() {
    // TODO: implement command
}

/**
 * Command usage: check-typos
 * Preconditions: RA should be loaded
 * On execute: Show the replacements that were automatically executed
 */
void CommandHandler::autocorrect() {
    // TODO: implement command
}

/**
 * Command usage: load <relation algebra filename>
 * Preconditions: File name should exist en contain code
 * On execute: Load the given RA in a RAExpression
 */
void CommandHandler::loadRA() {
    // TODO: implement command
}

/**
 * Command usage: check-conventions
 * Preconditions: RA should be loaded
 * On execute: For every replacement, print it and ask whether it should execute the replacement [Y/N]
 */
void CommandHandler::checkConventions() {
    // TODO: implement command
}

/**
 * Command usage: check-conventions
 * Preconditions: RA should be loaded
 * On execute: Show the replacements that were automatically executed
 */
void CommandHandler::autoConventions() {
    // TODO: implement command
}

/**
 * Command usage: to-sql <SQL output file>
 * Preconditions: RA should be loaded
 * On execute: Save generated SQL statement to the given file
 */
void CommandHandler::toSQL() {
    // TODO: implement command
}

void CommandHandler::lexify() {
    string expression;
    cout << "Expression: ";
    getline(cin, expression);
    Lexer lexer = Lexer(expression);
    auto t = lexer.tokenise(expression);
    for(Token s: t) {
        cout << toString[s.getType()] << " ";
    }
    cout << endl;
}
