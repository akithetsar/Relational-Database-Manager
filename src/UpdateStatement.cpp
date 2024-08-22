//
// Created by akith on 5/9/2024.
//

#include "UpdateStatement.h"

UpdateStatement::UpdateStatement(std::string table, std::vector <std::pair<std::string, std::string>> changes,
                                 Filter filter, std::shared_ptr <Database> db, std::string fullStatement)
        : Statement(std::move(db), std::move(fullStatement)), tableName(std::move(table)), changes(std::move(changes)),
          filter(std::move(filter)) {}

void UpdateStatement::test() { std::cout << "Update statement: " << tableName << ' ' << changes[0].first << std::endl; }

void UpdateStatement::execute() {
    Table &table = db->getTable(tableName);
    std::vector<int> indices = filter.filterOut(table);
    for (const auto &rowIndex: indices) {
        for (const auto &change: changes) {
            auto it = std::find_if(table.getColumns().begin(), table.getColumns().end(),
                                   [change](const std::string &col) { return col == change.first; });
            if (it != table.getColumns().end()) {
                int columnIndex = it - table.getColumns().begin();
                if(columnIndex < 0 | columnIndex > table.getColumns().size()) throw RuntimeError("No column at index: " + std::to_string(columnIndex) + " at statement " + fullStatement);
                table[rowIndex].updateData(columnIndex, change.second);
            }
        }
    }
    db->setChange(true);
}

std::shared_ptr <Statement>
UpdateStatement::parse(const std::string &fullStatement, const std::string &rest, const std::shared_ptr <Database> &db) {

    std::smatch match;
    std::string tableName;
    std::vector<std::shared_ptr<Condition>> conditions;
    std::vector<std::pair<std::string, std::string>> changes;
    if (std::regex_match(rest, match,
                         std::regex(
                                 "\\s*([\\w]+)\\s+(SET)\\s+([\\w=,\"'\\s]+)\\s+(WHERE)\\s*([\\w,\\s=><\"']*)"))) {
        std::smatch submatch;
        tableName = match[1];


        checkInvalidKeyword(match[1], fullStatement);
        checkTableNameValidity(tableName, fullStatement);
        checkForKeyword(match[2], "SET", fullStatement);
        checkForKeyword(match[4], "WHERE", fullStatement);


        changes = parseChanges(match[3].str(), fullStatement);
        conditions = parseConditions(match[5].str(), fullStatement);


        return std::make_shared<UpdateStatement>(tableName, changes, Filter(conditions), db, fullStatement);
    }
    else{
        throw SyntaxError("Syntax Error at: " + fullStatement);
    }


}
