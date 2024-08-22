//
// Created by akith on 5/9/2024.
//

#include <iomanip>
#include "Record.h"
#include "stringColoring.h"

Record::Record(std::vector <std::string> values) : data{std::move(values)} {}

const std::vector <std::string> &Record::getData() const { return data; }

std::ostream &operator<<(std::ostream &os, Record &record) {

    for (const auto &field: record.data) {
        os << field << '|';
    }
    return os;
}

void Record::updateData(int columnIndex, const std::string &value) {
    data[columnIndex] = value;
}

bool operator==(const Record &r1, const Record &r2) {
    return r1.data == r2.data;
}
