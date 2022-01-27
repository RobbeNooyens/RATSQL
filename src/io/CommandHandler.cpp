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
#include "../parser/EarleyParser.h"

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
    } else if(command == "parse") {
        parse();
    }
}
/**
 * Command usage: levdis <word> <max levenshtein distance>
 * Preconditions: /
 * On execute: prints all words that have a max levenshtein distance from a given string
 */
void CommandHandler::levDisCmd() {
}

/**
 * Command usage: check-typos
 * Preconditions: RA should be loaded
 * On execute: For every replacement, print it and ask whether it should execute the replacement [Y/N]
 */
void CommandHandler::checkTypos() {
}

/**
 * Command usage: check-typos
 * Preconditions: RA should be loaded
 * On execute: Show the replacements that were automatically executed
 */
void CommandHandler::autocorrect() {
}

/**
 * Command usage: load <relation algebra filename>
 * Preconditions: File name should exist en contain code
 * On execute: Load the given RA in a RAExpression
 */
void CommandHandler::loadRA() {
}

/**
 * Command usage: check-conventions
 * Preconditions: RA should be loaded
 * On execute: For every replacement, print it and ask whether it should execute the replacement [Y/N]
 */
void CommandHandler::checkConventions() {
}

/**
 * Command usage: check-conventions
 * Preconditions: RA should be loaded
 * On execute: Show the replacements that were automatically executed
 */
void CommandHandler::autoConventions() {
}

/**
 * Command usage: to-sql <SQL output file>
 * Preconditions: RA should be loaded
 * On execute: Save generated SQL statement to the given file
 */
void CommandHandler::toSQL() {
}

void CommandHandler::parse() {
    vector<ParseToken> tokens{
            {"PI", "pi"},
            {"NAME", "id"},
            {"ROUNDED_BRACKET_LEFT", "("},
            {"NAME", "Person"},
            {"ROUNDED_BRACKET_RIGHT", ")"}};
    std::string cfg = "../input/grammar.json";
    EarleyParser parser(cfg);
    parser.earleyParse(tokens);
}
