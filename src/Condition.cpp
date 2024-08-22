//
// Created by akith on 5/9/2024.
//
#include "Condition.h"
Condition::Condition(std::string column, std::string value) : column(std::move(column)), value(std::move(value)) {}

std::string Condition::getColumn() const {
    return column;
}

std::string Condition::getValue() const {
    return value;
}
