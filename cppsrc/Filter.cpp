//
// Created by akith on 5/9/2024.
//
#include "Filter.h"
Filter::Filter(std::vector <std::shared_ptr<Condition>> conditions) : conditions(std::move(conditions)) {}

std::vector<int> Filter::filterOut(const Table &table) {
    for (const auto &condition: conditions) {
        if (std::find(table.getColumns().begin(), table.getColumns().end(), condition->getColumn()) ==
            table.getColumns().end())
            throw RuntimeError(
                    "Column " + condition->getColumn() + "not found in table " + table.getName() + " at condition: " + condition->getColumn() + '=' + condition->getValue());
    }
    std::vector<int> indices;

    for (int i = 0; i < table.getRecords().size(); i++) {
        bool allConditions = true;
        for (const auto &condition: conditions) {
            allConditions &= condition->evaluate(table.getRecords()[i], table.getColumns());
        }
        if (allConditions) indices.push_back(i);

    }
    return indices;
}
