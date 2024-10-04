//
// Created by akith on 4/30/2024.
//

#ifndef DATABASEPOOP_CREATESTATEMENT_H
#define DATABASEPOOP_CREATESTATEMENT_H

#include "Statement.h"
#include <utility>
#include <vector>
#include "SyntaxExceptions.h"

class CreateStatement : public Statement {

public:
    /**
     * @brief Constructor for CreateStatement class.
     *
     * @param table The name of the table to be created.
     * @param columns A vector containing the names of columns for the table.
     * @param db A shared pointer to the Database object.
     * @param fullStatement The full statement string.
     *
     * @throws None.
     */
    CreateStatement(std::string table, std::vector<std::string> columns, std::shared_ptr<Database> db,
                    std::string fullStatement);

    /**
     * @brief Test function for CreateStatement class.
     *
     * @param None.
     *
     * @throws None.
     */
    void test();

    /**
     * @brief Executes the create statement.
     *
     * Adds a new table to the database with specified name and columns, and sets the change flag.
     *
     * @param None.
     *
     * @throws None.
     */
    void execute();

    /**
     * @brief Parses a full CREATE TABLE statement.
     *
     * Extracts table name and column names from the statement string, performs error handling,
     * and returns a shared pointer to a CreateStatement object.
     *
     * @param fullStatement The full statement string.
     * @param rest The remaining part of the statement after "CREATE TABLE".
     * @param db A shared pointer to the Database object.
     *
     * @return A shared pointer to a Statement object.
     *
     * @throws SyntaxError If there is a syntax error in the statement.
     */
    static std::shared_ptr<Statement> parse(const std::string &fullStatement, const std::string &rest,
                                            const std::shared_ptr<Database> &db);
private:
    std::string tableName;
    std::vector<std::string> columns;

};


#endif //DATABASEPOOP_CREATESTATEMENT_H
