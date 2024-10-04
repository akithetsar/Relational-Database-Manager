//
// Created by akith on 5/9/2024.
//
#include "DropStatement.h"

DropStatement::DropStatement(std::string tableName, std::shared_ptr <Database> db, std::string fullStatement) : Statement(
        std::move(db), std::move(fullStatement)), tableName(std::move(tableName)) {}

void DropStatement::test() { std::cout << "DROP Statement: " << tableName << std::endl; }

void DropStatement::execute() {
    db->removeTable(tableName);
    db->setChange(true);
}

std::shared_ptr <Statement>
DropStatement::parse(const std::string &fullStatement, const std::string &rest, const std::shared_ptr <Database> &db) {
    std::smatch match;

    if (std::regex_match(rest, match, std::regex("\\s*(TABLE)\\s+(\\w+)\\s*"))) {
        std::string tableName = match[2];
        checkForKeyword(match[1].str(), "TABLE", fullStatement);
        checkInvalidKeyword(match[2].str(), fullStatement);
        return std::make_shared<DropStatement>(tableName, db, fullStatement);
    } else {
        throw SyntaxError("Syntax Error at: " + fullStatement);
    }

}
