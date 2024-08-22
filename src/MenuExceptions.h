//
// Created by akith on 5/6/2024.
//

#ifndef DATABASEPOOP_MENUEXCEPTIONS_H
#define DATABASEPOOP_MENUEXCEPTIONS_H

#include <exception>
#include <utility>
#include <string>

#include <fstream> // Include this header for std::ofstream
class InvalidMenuChoiceException : public std::exception {

public:
    explicit InvalidMenuChoiceException(std::string msg) : msg(std::move(msg)) {}

    const char *what() const noexcept override {
        std::string errorMessage = std::string("MENU EXCEPTION: ") + msg;
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    std::string msg;
};

#endif //DATABASEPOOP_MENUEXCEPTIONS_H
