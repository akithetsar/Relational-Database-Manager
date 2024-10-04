//
// Created by akith on 5/6/2024.
//

#ifndef DATABASEPOOP_TABLEEXCEPTIONS_H
#define DATABASEPOOP_TABLEEXCEPTIONS_H
#include <exception>
#include <string>
#include <fstream>

class recordIndexOutOfBoundsException : public std::exception {

public:
    explicit recordIndexOutOfBoundsException(std::string name, int index) : tableName(std::move(name)), index(index) {}

    const char *what() const noexcept override {

        std::string errorMessage = std::string("TABLE EXCEPTION: ") + "Table " + tableName + " doesn't have a record at index " + std::to_string(index);
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    std::string tableName;
    int index;
};


class ColumnValueMissmatchException : public std::exception {

public:
    explicit ColumnValueMissmatchException(int columnSize, int recordSize) : columnSize(columnSize), recordSize(recordSize) {}

    const char *what() const noexcept override {

        std::string errorMessage = std::string("TABLE EXCEPTION: ") + "Table has " + std::to_string(columnSize) + " but " +
                                                                      std::to_string(recordSize) + " values were provided.";
        std::ofstream errorOutput("errorFile.txt", std::ios::out);
        errorOutput << errorMessage << '\n';
        errorOutput.close();
        return errorMessage.c_str();
    }


private:
    int columnSize;
    int recordSize;
};
#endif //DATABASEPOOP_TABLEEXCEPTIONS_H
