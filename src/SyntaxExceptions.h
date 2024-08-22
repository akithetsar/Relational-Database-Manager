//
// Created by akith on 5/6/2024.
//

#ifndef DATABASEPOOP_SYNTAXEXCEPTIONS_H
#define DATABASEPOOP_SYNTAXEXCEPTIONS_H

#include <exception>
#include <utility>
#include <string>
#include <fstream>


class SyntaxError : public std::exception {

public:
    explicit SyntaxError(std::string msg) : msg(std::move(msg)) {}

    const char *what() const noexcept override {
        std::string errorMessage = std::string("SYNTAX EXCEPTION: ") + msg;
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    std::string msg;

};


#endif //DATABASEPOOP_SYNTAXEXCEPTIONS_H
