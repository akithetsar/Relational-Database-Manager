//
// Created by akith on 5/9/2024.
//

#include "ShowStatement.h"
ShowStatement::ShowStatement(std::shared_ptr <Database> db, std::string fullStatement) : Statement(std::move(db), std::move(fullStatement)) {}

void ShowStatement::test() {
    std::cout << "Delete statement: " << tableName << ' ' << std::endl;
}

void ShowStatement::execute() {
    db->drawTables();
}

std::shared_ptr <Statement>
ShowStatement::parse(const std::string &fullStatement, const std::string &rest, const std::shared_ptr <Database> &db) {
    std::smatch match;
    if (std::regex_match(rest, std::regex("\\s*TABLES\\s*"))) {
        return std::make_shared<ShowStatement>(db, fullStatement);
    } else {
        throw SyntaxError("Syntax Error at: " + fullStatement);
    }
}
