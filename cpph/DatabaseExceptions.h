//
// Created by akith on 5/6/2024.
//

#ifndef DATABASEPOOP_DATABASEEXCEPTIONS_H
#define DATABASEPOOP_DATABASEEXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>
#include <fstream>

class TableAlreadyExistsException : public std::exception {

public:
    explicit TableAlreadyExistsException(std::string tableName) : tableName(std::move(tableName)) {}

    const char *what() const noexcept override {

        std::string errorMessage = std::string("DATABASE EXCEPTION: ") + "Table with the table name: " + tableName +
                                   " already exists in this database.";
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    std::string tableName;
};

class TableDoesntExistsException : public std::exception {

public:
    explicit TableDoesntExistsException(std::string tableName) : tableName(std::move(tableName)) {}

    const char *what() const noexcept override {

        std::string errorMessage = std::string("DATABASE EXCEPTION: ") + "Table with the tableName" + tableName +
                                   " doesn\'t exists in this database.";
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    std::string tableName;
};

class DatabaseNotLoadedException : public std::exception {

public:
    explicit DatabaseNotLoadedException() {}

    const char *what() const noexcept override {

        std::string errorMessage = "DATABASE EXCEPTION: No database is loaded";
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


};


#endif //DATABASEPOOP_DATABASEEXCEPTIONS_H
