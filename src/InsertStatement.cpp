//
// Created by akith on 5/9/2024.
//
#include "InsertStatement.h"

InsertStatement::InsertStatement(std::string tableName, std::vector <Record> records, std::vector <std::string> columns,
                                 std::shared_ptr <Database> db, std::string fullStatement) : Statement(std::move(db),
                                                                                                       std::move(fullStatement)),
                                                                                             tableName(std::move(
                                                                                                     tableName)),
                                                                                             records(std::move(records)),
                                                                                             columns(std::move(columns)) {}

void InsertStatement::test() {
    std::cout << "Insert Statement: " << tableName << ' ' << records[0] << ' ' << columns[0] << std::endl;
}

void InsertStatement::execute() {

    std::vector<std::string> columnNames = db->getTable(tableName).getColumns();
    if(columnNames.size() != columns.size()) throw RuntimeError("Columns not matching size at: " + fullStatement);
    for (int i = 0; i < columns.size(); i++) {
        if (columns[i] != columnNames[i]) { throw RuntimeError("Columns not matching names at: " + fullStatement); }
    }

    for (const auto &record: records) {
        db->insertRecord(tableName, record);
    }
    db->setChange(true);
}

std::shared_ptr <Statement>
InsertStatement::parse(const std::string &fullStatement, const std::string &rest, const std::shared_ptr <Database> &db) {
    std::smatch match;
    std::vector<std::string> columns;
    std::string tableName;
    std::vector<Record> records;
    if (std::regex_match(rest, match, std::regex(
            "\\s*(INTO)\\s+([A-Za-z]+)\\s+\\(([\\w,\\s]*)\\)\\s+(VALUES)\\s+([()\\w,\"\\s\']+)\\s*"))) {
        std::smatch submatch;
        tableName = match[2];

        checkForKeyword(match[1], "INTO", fullStatement);
        checkForKeyword(match[4], "VALUES", fullStatement);
        checkInvalidKeyword(match[2], fullStatement);


        columns = parseColumns(match[3].str(), fullStatement);
        records = parseRecords(match[5].str(), fullStatement);


        return std::make_shared<InsertStatement>(tableName, records, columns, db, fullStatement);
    } else {
        throw SyntaxError("Syntax Error at: " + fullStatement);
    }
}
