//
// Created by akith on 5/9/2024.
//

#include <fstream>
#include "Database.h"
#include "Query.h"
#include <fstream>
#include "Format.h"
Database::Database(std::string name) : name{std::move(name)}, filePath(nullptr), change(false) {


}

void Database::addTable(const std::string &tableName, const Table &table) {

    if (tables.find(tableName) != tables.end())
        throw TableAlreadyExistsException(tableName);

    tables.insert({tableName, table});

}

void Database::removeTable(const std::string &tableName) {

    if (tables.erase(tableName) == 0)
        throw TableDoesntExistsException(tableName);

}

Table &Database::getTable(const std::string &tableName) {
    if (tables.find(tableName) == tables.end())
        throw TableDoesntExistsException(tableName);
    return tables[tableName];
}

std::unordered_map <std::string, Table> &Database::getTables() {
    return tables;
}

std::string Database::getName() {
    return name;
}

void Database::drawTables() {


    for (auto &table: tables) {
        std::cout << table.second << "\n\n";


    }

}

void Database::insertRecord(const std::string &tableName, const Record &record) {
    tables[tableName].addRecord(record);
}

std::ostream &operator<<(std::ostream &os, Database &database) {
std::ofstream bufferOutput("bufferFile.txt", std::ios::out);
    os << "DATABASE " << database.name << '\n';
    for (auto &table: database.tables) {
        os << table.second << '\n';
        bufferOutput << table.second << "\n\n";
    }
    bufferOutput.close();
    return os;
}

void Database::setFilePath(const std::string &path) {
    filePath = std::make_shared<std::string>(path);
}

std::shared_ptr <std::string> Database::getFilePath() {
    return filePath;
}

bool Database::isChanged() const {
    return change;
}

void Database::setChange(bool changed) {
    change = changed;
}

void Database::executeQuery(std::shared_ptr<Database> currDb, const std::string& queryText) {

        try {

            Query query(currDb, queryText);
            query.execute();

        }
        catch(const std::exception &exception) {

            std::cout << exception.what();
        }
}
std::shared_ptr<Database> Database::loadDatabase(const std::string &path) {

    Database old = *this;
    std::shared_ptr<Database> temp;

    try{
       temp = Format::loadDatabase(path);

    }
    catch(const std::exception &exception){
       *this = old;
       std::cout << exception.what();
    }
    return temp;
}

void Database::exportToSQL(const std::string& path){
    if (this == nullptr)
        throw DatabaseNotLoadedException();
    std::cout << "testsql";
    std::shared_ptr<Database> db = std::make_shared<Database>(*this);
    Format::exportDatabaseToSql(path, db);
}

void Database::exportToCustom(const std::string& filePath){
    if (this == nullptr)
        throw DatabaseNotLoadedException();

    std::cout << "testcustom";
    std::string path = filePath + this->getName() + ".customSQL";
    std::shared_ptr<Database> db = std::make_shared<Database>(*this);
    Format::exportDatabaseToCustom(path, db);
}
