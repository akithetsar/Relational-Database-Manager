//
// Created by akith on 4/19/2024.
//

#ifndef DATABASEPOOP_DATABASE_H
#define DATABASEPOOP_DATABASE_H

#include <utility>

#include "Table.h"

#include <unordered_map>
#include <memory>
#include <limits>
#include "DatabaseExceptions.h"




class Database {


public:


    /**
      * @brief Constructs a Database object with a given name.
      * @param name The name of the database.
      */
    explicit Database(std::string name);

    /**
     * @brief Adds a table to the database.
     * @param tableName The name of the table to be added.
     * @param table The table object to be added.
     * @throws TableAlreadyExistsException If a table with the same name already exists.
     */
    void addTable(const std::string &tableName, const Table &table);

    /**
     * @brief Removes a table from the database.
     * @param tableName The name of the table to be removed.
     * @throws TableDoesntExistsException If the specified table doesn't exist.
     */
    void removeTable(const std::string &tableName);

    /**
     * @brief Retrieves a reference to a table in the database.
     * @param tableName The name of the table to retrieve.
     * @return Reference to the specified table.
     * @throws TableDoesntExistsException If the specified table doesn't exist.
     */
    Table &getTable(const std::string &tableName);

    /**
     * @brief Retrieves a reference to the tables in the database.
     * @return Reference to the unordered map of tables.
     */
    std::unordered_map<std::string, Table> &getTables();

    /**
     * @brief Retrieves the name of the database.
     * @return The name of the database.
     */
    std::string getName();

    /**
     * @brief Displays the tables in the database.
     */
    void drawTables();

    /**
     * @brief Inserts a record into the specified table.
     * @param tableName The name of the table to insert the record into.
     * @param record The record to insert.
     */
    void insertRecord(const std::string &tableName, const Record &record);

    /**
     * @brief Stream insertion operator overload to output the database.
     * @param os The output stream.
     * @param database The database to be output.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, Database &database);

    /**
     * @brief Sets the file path for the database.
     * @param path The file path to set.
     */
    void setFilePath(const std::string &path);

    /**
     * @brief Retrieves the file path of the database.
     * @return A shared pointer to the file path string.
     */
    std::shared_ptr<std::string> getFilePath();

    /**
     * @brief Checks if the database has been changed.
     * @return True if the database has been changed, false otherwise.
     */
    bool isChanged() const;

    /**
     * @brief Sets the change status of the database.
     * @param changed True if the database has been changed, false otherwise.
     */
    void setChange(bool changed);

    void executeQuery(std::shared_ptr<Database> currDb, const std::string& querytext);

    std::shared_ptr<Database> loadDatabase(const std::string& path);

    void exportToSQL(const std::string& path);
    void exportToCustom(const std::string& path);

private:
    std::unordered_map<std::string, Table> tables;
    std::string name;
    std::shared_ptr<std::string> filePath;

    bool change;

public:

};

#endif //DATABASEPOOP_DATABASE_H
