/**
 *  ╒══════════════════════════════════════════════════╕
 *  │                                                  │
 *  │                 RATSQL Project                   │
 *  │            Relational Algebra To SQL             │
 *  │                                                  │
 *  │  Contributors: Pablo Deputter, Cédric Leclercq,  │
 *  │               Robbe Nooyens, Maarten Peirsman    │
 *  │                                                  │
 *  │   University of Antwerp - Advanced Programming   │
 *  │                                                  │
 *  ╘══════════════════════════════════════════════════╛
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
    // TODO: refactor to CommandHandler
    /*
    std::cout << std::boolalpha << LevenshteinDistance::evalLevenshteinDistance("ikCEDRICbencoolenjijniet",
                                                                                "ikbencoolenjijniet", 6) << "\n";
    */
    while(true) {
        getline(std::cin, cmd);
        if (cmd == "exit") {
            std::cout << "Exiting now..." << std::endl;
            return 0;
        }
        else if (cmd.size() > 2 and cmd.substr(0,2) == "LD") {
            std::string input = cmd.substr(3,cmd.size()-1);
            std::string maxDistanceStr;
            try {
                for (auto ch: input) {
                    if (ch == ' ') break;
                    else maxDistanceStr += ch;
                }
                int maxDistance = -1;
                std::string ldPre1 = cmd.substr(5 + maxDistanceStr.size(), cmd.size() - 1);
                if (cmd.substr(4 + maxDistanceStr.size(), cmd.size() - 1).front() != '"') {
                    throw(std::exception());
                }
                std::string ldStr1;
                for (auto ch: ldPre1) {
                    if (ch == '"') break;
                    else ldStr1 += ch;
                }
                std::string ldPre2 = cmd.substr(8 + maxDistanceStr.size() + ldStr1.length(), cmd.size() - 1);
                if (cmd.substr(7 + maxDistanceStr.size() + ldStr1.length(), cmd.size() - 1).front() != '"') {
                    throw(std::exception());
                }
                std::string ldStr2;
                for (auto ch: ldPre2) {
                    if (ch == '"') break;
                    else ldStr2.push_back(ch);
                }

                maxDistance = std::stoi(maxDistanceStr);
                std::cout << "Levenshtein distance result for your given max distance is: ";
                std::cout << std::boolalpha
                          << LevenshteinDistance::evalLevenshteinDistance(ldStr1, ldStr2, maxDistance);
                std::cout << std::endl;
            } catch(std::exception& exc) {
                std::cerr << "ERROR - A command for levenshtein distance should be like this: " << std::endl;
                std::cerr << R"(LD <maxDistance> "<string 1>" "<string 2>")" << std::endl;
            }


            // Optie 1, de twee strings worden gesplitst door allebei in haakjes te staan

            /*
            // Optie 2, de twee strings worden als input gevraagd
            std::string str1,str2;
            std::cout << "String 1: ";
            getline(std::cin,str1);
            std::cout << std::endl << "String 2: ";
            getline(std::cin, str2);
            std::cout << std::endl;
             */
        }
        else if (cmd.size() > 3 and cmd.substr(0,3) == "run") {
            std::string input = cmd.substr(4,cmd.size()-1);
            std::cout << input << std::endl;
        }
    }
//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    return 69;
    //return QApplication::exec();
    return 0;
}
