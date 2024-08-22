//
// Created by akith on 4/30/2024.
//

#ifndef DATABASEPOOP_DROPSTATEMENT_H
#define DATABASEPOOP_DROPSTATEMENT_H

#include "Statement.h"
#include <iostream>
#include <utility>

class DropStatement : public Statement {

public:

    /**
      * @brief Constructor for DropStatement.
      *
      * @param tableName The name of the table to be dropped.
      * @param db A shared pointer to the database object.
      * @param fullStatement The full statement string.
      */
    DropStatement(std::string tableName, std::shared_ptr<Database> db, std::string fullStatement);

    /**
     * @brief Test function to print DROP statement information.
     */
    void test();

    /**
     * @brief Execute the DROP statement by removing the specified table from the database.
     *
     * Marks the database as changed.
     */
    void execute();

    /**
     * @brief Parse the DROP statement.
     *
     * @param fullStatement The full DROP statement string.
     * @param rest The remaining part of the statement after the DROP keyword.
     * @param db A shared pointer to the database object.
     * @return A shared pointer to the parsed DropStatement.
     * @throws SyntaxError if there is a syntax error in the statement.
     */
    static std::shared_ptr<Statement> parse(const std::string& fullStatement, const std::string& rest, const std::shared_ptr<Database>& db);

private:
    std::string tableName;

};

#endif //DATABASEPOOP_DROPSTATEMENT_H
