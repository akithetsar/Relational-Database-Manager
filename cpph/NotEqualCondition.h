//
// Created by akith on 5/1/2024.
//

#ifndef DATABASEPOOP_NOTEQUALCONDITION_H
#define DATABASEPOOP_NOTEQUALCONDITION_H

#include "Condition.h"

#include <utility>
#include <algorithm>

class NotEqualCondition : public Condition {

public:

    /**
     * @brief Constructs a NotEqualCondition object.
     *
     * @param column The column name for the condition.
     * @param value The value to compare against.
     */
    NotEqualCondition(std::string column, std::string value);

    /**
     * @brief Evaluates if the record satisfies the not equal condition.
     *
     * @param record The record to evaluate.
     * @param columns The vector of column names in the record.
     * @return True if the condition is satisfied, otherwise false.
     */
    bool evaluate(const Record &record, const std::vector<std::string> &columns);

private:


};

#endif //DATABASEPOOP_NOTEQUALCONDITION_H
