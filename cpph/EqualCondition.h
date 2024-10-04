//
// Created by akith on 5/1/2024.
//

#ifndef DATABASEPOOP_EQUALCONDITION_H
#define DATABASEPOOP_EQUALCONDITION_H

#include "Condition.h"

#include <utility>
#include <algorithm>

class EqualCondition : public Condition {

public:
/**
     * @brief Constructor for EqualCondition.
     *
     * @param column The column to compare.
     * @param value The value to compare against.
     */
    EqualCondition(std::string column, std::string value);

    /**
     * @brief Evaluate the equality condition.
     *
     * @param record The record to evaluate.
     * @param columns The list of columns in the record.
     * @return True if the condition is satisfied, false otherwise.
     */
    bool evaluate(const Record& record, const std::vector<std::string>& columns) override;;

private:


};


#endif //DATABASEPOOP_EQUALCONDITION_H
