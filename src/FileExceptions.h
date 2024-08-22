//
// Created by akith on 5/6/2024.
//

#ifndef DATABASEPOOP_FILEEXCEPTIONS_H
#define DATABASEPOOP_FILEEXCEPTIONS_H

#include <exception>
#include <utility>
#include <string>


class FileNotFoundException : public std::exception {

public:
    explicit FileNotFoundException(std::string msg) : msg(std::move(msg)) {}

    const char *what() const noexcept override {
        std::string errorMessage = std::string("FILE EXCEPTION: ") + msg;
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    std::string msg;
};

class IncorrectFileFormat : public std::exception {

public:
    explicit IncorrectFileFormat(std::string path) : path(std::move(path)) {}

    const char *what() const noexcept override {
        std::string errorMessage = std::string("FILE EXCEPTION: Contents of file ") + path + " are incorrectly formated";
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    std::string path;
};
class IncorrectFileType : public std::exception {

public:
    explicit IncorrectFileType(std::string path) : path(std::move(path)) {}

    const char *what() const noexcept override {
        std::string errorMessage = std::string("FILE EXCEPTION: File ") + path + " is the incorrect formta type";
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    std::string path;
};

#endif //DATABASEPOOP_FILEEXCEPTIONS_H
