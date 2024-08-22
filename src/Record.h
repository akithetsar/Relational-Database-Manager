//
// Created by akith on 4/24/2024.
//


#ifndef DATABASEPOOP_RECORD_H
#define DATABASEPOOP_RECORD_H

#include <iostream>
#include <utility>
#include <vector>
#include "TableExceptions.h"

class Record {

public:

    /**
     * @brief Constructor for Record class.
     * @param values A vector of strings representing the record data.
     */
    Record(std::vector<std::string> values);

    /**
     * @brief Getter for the record data.
     * @return A constant reference to the vector of strings containing the record data.
     */
    const std::vector<std::string>& getData() const;

    /**
     * @brief Updates the data at the specified column index.
     * @param columnIndex The index of the column to update.
     * @param value The new value for the specified column.
     */
    void updateData(int columnIndex, const std::string& value);


/**
 * @brief Overloaded stream insertion operator for printing Record objects.
 * @param os The output stream.
 * @param record The Record object to be printed.
 * @return A reference to the output stream.
 */
friend std::ostream& operator<<(std::ostream& os, Record& record);

/**
 * @brief Overloaded equality operator for comparing two Record objects.
 * @param r1 The first Record object.
 * @param r2 The second Record object.
 * @return True if the two Record objects are equal, false otherwise.
 */
friend bool operator==(const Record& r1, const Record& r2);


private:


    std::vector<std::string> data;
};


#endif //DATABASEPOOP_RECORD_H
