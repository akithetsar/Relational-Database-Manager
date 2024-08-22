//
// Created by akith on 5/9/2024.
//

#include "Table.h"
#include <iomanip>
#include <fstream>
#include "stringColoring.h"
Table::Table(std::string tableName, std::vector<std::string> columnNames) : name{std::move(tableName)},
                                                                            columnNames{std::move(columnNames)} {}

Table Table::createSubsetTable(std::vector<std::string> &subColumnNames, std::vector<int> filterIndices) {
    Table subTable("Selected Table", subColumnNames);
    int index = 0;
    for (const auto &record: records) {
        if (std::find(filterIndices.begin(), filterIndices.end(), index) == filterIndices.end()) {
            index++;
            continue; // skip if record is not in filtered
        }
        std::vector<std::string> subData(subColumnNames.size());
        for (int col = 0; col < columnNames.size(); col++) {
            for (int i = 0; i < subColumnNames.size(); i++) {
                if (subColumnNames[i] == columnNames[col]) {
                    subData[i] = record.getData()[col];
                }
            }
        }
        subTable.addRecord(Record(subData));
        index++;
    }
    return subTable;
}

const std::vector<Record> &Table::getRecords() const {
    return records;
}

std::ostream &operator<<(std::ostream &os, Table &table) {
    std::ofstream bufferOutput("bufferFile.txt", std::ios::app);




    os << "TABLE " << table.name << '\n';
    bufferOutput << table.name << '\n';
    for (auto &column: table.columnNames) {
//        os <<  std::setw(25) << colorString("[", COLOR_BLUE) << colorString(column, COLOR_BLUE) << colorString("]", COLOR_BLUE) << std::setw(25)<< "\t";
        bufferOutput << column << '/';
    }
    std::cout << '\n';
    bufferOutput << '\n';
    for (auto &record: table.records) {
        os << record << '\n';
        bufferOutput << record << '\n';
    }
    bufferOutput << '@' << '\n';
    bufferOutput.close();

    return os;
}

void Table::eraseRecords(const std::vector<int> &indices) {
    int counter = 0;
    for (const auto &i: indices) {
        records.erase(records.begin() + i - counter);
        counter++;
    }
}

Record &Table::operator[](int i) {
    if (i < 0 || i > records.size() - 1)
        throw recordIndexOutOfBoundsException(name, i);
    return records[i];
}

void Table::addRecord(const Record &record) {
    if (record.getData().size() != columnNames.size())
        throw ColumnValueMissmatchException(columnNames.size(), record.getData().size());
    records.push_back(record);
}

const std::vector<std::string> &Table::getColumns() const {
    return columnNames;
}

const std::string &Table::getName() const { return name; }
