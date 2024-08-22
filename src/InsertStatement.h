//
// Created by akith on 5/1/2024.
//

#ifndef DATABASEPOOP_INSERTSTATEMENT_H
#define DATABASEPOOP_INSERTSTATEMENT_H

#include "Statement.h"
#include "Record.h"

#include <utility>
#include <vector>


class InsertStatement : public Statement {

public:
    /**
     * @brief Constructs an InsertStatement object.
     *
     * @param tableName The name of the table to insert records into.
     * @param records A vector containing the records to be inserted.
     * @param columns A vector containing the column names for the insertion.
     * @param db A shared pointer to the Database object.
     * @param fullStatement The full insert statement.
     */
    InsertStatement(std::string tableName, std::vector<Record> records, std::vector<std::string> columns,
                    std::shared_ptr<Database> db, std::string fullStatement);

    /**
     * @brief Test function to display the details of the insert statement.
     */
    void test();

    /**
     * @brief Executes the insert statement, inserting records into the specified table.
     *
     * @throws RuntimeError If column sizes or names do not match.
     */
    void execute();

    /**
     * @brief Parses the insert statement and returns an InsertStatement object.
     *
     * @param fullStatement The full insert statement.
     * @param rest The portion of the statement to be parsed.
     * @param db A shared pointer to the Database object.
     * @return A shared pointer to the parsed InsertStatement object.
     * @throws SyntaxError If there is a syntax error in the statement.
     */
    static std::shared_ptr<Statement> parse(const std::string &fullStatement, const std::string &rest,
                                            const std::shared_ptr<Database> &db);

private:
    std::string tableName;
    std::vector<Record> records;
    std::vector<std::string> columns;
};

#endif //DATABASEPOOP_INSERTSTATEMENT_H
