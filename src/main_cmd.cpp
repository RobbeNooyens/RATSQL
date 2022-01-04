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

#include <iostream>
#include "algorithms/LevenshteinDistance.h"
#include "io/CommandHandler.h"


enum CmdColor {GREEN, WHITE, BLUE};

std::string color(std::string str, CmdColor color) {
    std::string result;
    switch (color) {
        case GREEN:
            result = "\x1B[92m";
            break;
        case WHITE:
            result = "\x1B[97m";
            break;
        case BLUE:
            result = "\x1B[94m";
            break;
    }
    result.append(str).append("\033[0m");
    return result;
}

int main(int argc, char *argv[]) {
    CommandHandler handleCommand;
    std::string cmd;
    while(cmd != "exit") {
        std::cout << color("root@laptop", GREEN) << color(":", WHITE) << color("~/Programs/RATSQL$ ", BLUE);
        getline(std::cin, cmd);
        handleCommand(cmd);
    }
    return 0;
}
