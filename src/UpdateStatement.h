//
// Created by akith on 5/1/2024.
//

#ifndef DATABASEPOOP_UPDATESTATEMENT_H
#define DATABASEPOOP_UPDATESTATEMENT_H

#include "Statement.h"

#include <utility>
#include "Filter.h"

class UpdateStatement : public Statement {

public:
    /**
    * @brief Constructor for UpdateStatement class.
    * @param table The name of the table to be updated.
    * @param changes The changes to be applied to the table.
    * @param filter The filter to apply updates to specific records.
    * @param db A shared pointer to a Database object.
    * @param fullStatement The full statement to be executed.
    */
    UpdateStatement(std::string table, std::vector<std::pair<std::string, std::string>> changes, Filter filter, std::shared_ptr<Database> db, std::string fullStatement);

    /**
     * @brief Test function for UpdateStatement.
     */
    void test() override;

    /**
     * @brief Executes the update statement.
     */
    void execute() override;

    /**
     * @brief Parses an update statement.
     * @param fullStatement The full update statement.
     * @param rest The remaining part of the statement after the initial command.
     * @param db A shared pointer to a Database object.
     * @return A shared pointer to the parsed UpdateStatement object.
     * @throws SyntaxError if the statement syntax is incorrect.
     */
    static std::shared_ptr<Statement> parse(const std::string& fullStatement, const std::string& rest, const std::shared_ptr<Database>& db);


private:
    std::string tableName;
    std::vector<std::pair<std::string, std::string>> changes;
    Filter filter;

};

#endif //DATABASEPOOP_UPDATESTATEMENT_H
