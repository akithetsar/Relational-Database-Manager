//
// Created by akith on 5/9/2024.
//
#include "CreateStatement.h"

CreateStatement::CreateStatement(std::string table, std::vector <std::string> columns, std::shared_ptr <Database> db,
                                 std::string fullStatement) : Statement(
        std::move(db), std::move(fullStatement)), tableName(
        std::move(table)), columns(std::move(columns)) {}

void CreateStatement::test() { std::cout << "Create statement: " << tableName << ' ' << columns[0] << std::endl; }

void CreateStatement::execute() {
    db->addTable(tableName, Table(tableName, columns));
    db->setChange(true);
}

std::shared_ptr <Statement>
CreateStatement::parse(const std::string &fullStatement, const std::string &rest, const std::shared_ptr <Database> &db) {
    std::string tableName;
    std::vector<std::string> columns;
    std::smatch match;
    if (std::regex_match(rest, match, std::regex("\\s*(TABLE)\\s+(\\w*)\\s+\\(([\\w,\\s]*)\\)\\s*"))) {
        std::smatch submatch;
        tableName = match[2];
        //Error Handling
        Statement::checkForKeyword(match[1], "TABLE", fullStatement);
        Statement::checkInvalidKeyword(match[2].str(), fullStatement);
        Statement::checkTableNameValidity(tableName, fullStatement);


        columns = Statement::parseColumns(match[3].str(), fullStatement);


        return std::make_shared<CreateStatement>(tableName, columns, db, fullStatement);

    } else {
        throw SyntaxError("Syntax Error at: " + fullStatement);
    }
}
