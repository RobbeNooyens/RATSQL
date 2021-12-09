#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "algorithms/LevenshteinDistance.h"
#include "algorithms/ShuntingAlgorithm.h"

int main(int argc, char *argv[]) {


    /*
    std::cout << std::boolalpha << LevenshteinDistance::evalLevenshteinDistance("ikCEDRICbencoolenjijniet",
                                                                                "ikbencoolenjijniet", 6) << "\n";
    */
    std::string cmd;
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
    ShuntingAlgorithm algorithm;
    algorithm(input);
    return 0;
}
