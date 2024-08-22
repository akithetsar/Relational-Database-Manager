//
// Created by akith on 5/1/2024.
//

#ifndef DATABASEPOOP_CONDITION_H
#define DATABASEPOOP_CONDITION_H

#include <iostream>
#include <utility>
#include <vector>
#include "Record.h"

class Condition {


public:


/// Constructs a Condition object with the given column name and value.
    ///
    /// \param column The name of the column.
    /// \param value The value to be compared.
    Condition(std::string column, std::string value);

    /// Gets the column name associated with the condition.
    ///
    /// \return The column name.
    std::string getColumn() const;

    /// Gets the value associated with the condition.
    ///
    /// \return The value.
    std::string getValue() const;

    virtual bool evaluate(const Record &, const std::vector<std::string> &) = 0;

protected:
    std::string column;
    std::string value;

};

#endif //DATABASEPOOP_CONDITION_H
