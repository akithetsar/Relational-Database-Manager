//
// Created by akith on 5/1/2024.
//

#ifndef DATABASEPOOP_FILTER_H
#define DATABASEPOOP_FILTER_H

#include <iostream>
#include <utility>
#include <vector>
#include <memory>

#include "Condition.h"
#include "Table.h"
#include "RuntimeErrorExceptions.h"

class Filter {

public:
    /**
        * @brief Constructor for Filter.
        *
        * @param conditions A vector of shared pointers to conditions.
        */
    Filter(std::vector<std::shared_ptr<Condition>> conditions);

    /**
     * @brief Filters out indices of records in the table satisfying all conditions.
     *
     * @param table The table to filter.
     * @return A vector of indices of records satisfying all conditions.
     * @throws RuntimeError if a condition refers to a column not found in the table.
     */
    std::vector<int> filterOut(const Table& table);


private:
    std::vector<std::shared_ptr<Condition>> conditions;


};

#endif //DATABASEPOOP_FILTER_H
