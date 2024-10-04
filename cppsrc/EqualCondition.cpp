//
// Created by akith on 5/9/2024.
//
#include "EqualCondition.h"
EqualCondition::EqualCondition(std::string column, std::string value) : Condition(std::move(column), std::move(value)) {}

bool EqualCondition::evaluate(const Record &record, const std::vector <std::string> &columns) {
    std::string& c = column;
    int index = std::find_if(columns.begin(), columns.end(),[c](const std::string& col){return col == c;}) - columns.begin();
    return record.getData()[index] == value;
}
