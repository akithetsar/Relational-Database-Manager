//
// Created by akith on 5/9/2024.
//

#include "DeleteStatement.h"
DeleteStatement::DeleteStatement(std::string tableName, Filter filter, std::shared_ptr <Database> db,
                                 std::string fullStatement) : Statement(std::move(db), std::move(fullStatement)),
                                                              tableName(
                                                                      std::move(tableName)),
                                                              filter(std::move(filter)) {}

void DeleteStatement::test() {
    std::cout << "Delete statement: " << tableName << ' ' << std::endl;
}

void DeleteStatement::execute() {

    std::vector<int> indices = filter.filterOut(db->getTable(tableName));
    db->getTable(tableName).eraseRecords(filter.filterOut(db->getTable(tableName)));
    db->setChange(true);

}

std::shared_ptr<Statement>
DeleteStatement::parse(const std::string &fullStatement, const std::string &rest, const std::shared_ptr<Database> &db) {
    std::smatch match;
    std::string tableName;
    std::vector<std::shared_ptr<Condition>> conditions;
    if (std::regex_match(rest, match,
                         std::regex("\\s*(FROM)\\s+(\\w+)\\s+(WHERE)\\s+([\\w,\\s=><\"\']*)\\s*"))) {
        std::smatch submatch;
        tableName = match[2];

        checkForKeyword(match[1].str(), "FROM", fullStatement);
        checkForKeyword(match[3].str(), "WHERE", fullStatement);
        checkInvalidKeyword(match[2], fullStatement);
        checkTableNameValidity(tableName, fullStatement);

        conditions = parseConditions(match[4].str(), fullStatement);

        return std::make_shared<DeleteStatement>(tableName, Filter(conditions), db, fullStatement);
    } else {
        throw SyntaxError("Syntax Error at: " + fullStatement);
    }

}
