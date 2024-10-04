//
// Created by akith on 4/25/2024.
//

#ifndef DATABASEPOOP_TABLE_H
#define DATABASEPOOP_TABLE_H

#include <utility>
#include <vector>
#include <algorithm>
#include "Record.h"

#include "TableExceptions.h"


class Table {

public:
    Table() = default;
    /**
     * @brief Constructor for Table class.
     * @param tableName The name of the table.
     * @param columnNames The names of the columns in the table.
     */
    Table(std::string tableName, std::vector<std::string> columnNames);

    /**
     * @brief Creates a subset table based on given column names and filter indices.
     * @param subColumnNames The names of the columns in the subset table.
     * @param filterIndices The indices used to filter records.
     * @return The subset table.
     */
    Table createSubsetTable(std::vector<std::string>& subColumnNames, std::vector<int> filterIndices);

    /**
     * @brief Retrieves the records of the table.
     * @return A reference to the vector of records.
     */
    const std::vector<Record>& getRecords() const;

    /**
     * @brief Overloaded output stream operator to print the table.
     * @param os The output stream.
     * @param table The table to be printed.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, Table& table);

    /**
     * @brief Erases records from the table based on given indices.
     * @param indices The indices of records to be erased.
     */
    void eraseRecords(const std::vector<int>& indices);

    /**
     * @brief Overloaded subscript operator to access records by index.
     * @param i The index of the record to access.
     * @return A reference to the record.
     * @throws recordIndexOutOfBoundsException if the index is out of bounds.
     */
    Record& operator[](int i);

    /**
     * @brief Adds a record to the table.
     * @param record The record to be added.
     * @throws ColumnValueMissmatchException if the record size does not match the number of columns.
     */
    void addRecord(const Record& record);

    /**
     * @brief Retrieves the names of columns in the table.
     * @return A reference to the vector of column names.
     */
    const std::vector<std::string>& getColumns() const;

    /**
     * @brief Retrieves the name of the table.
     * @return The name of the table.
     */
    const std::string& getName() const;

private:

    std::string name;
    std::vector<std::string> columnNames;
    std::vector<Record> records;


};



#endif //DATABASEPOOP_TABLE_H
