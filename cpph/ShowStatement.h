//
// Created by akith on 5/6/2024.
//

#ifndef DATABASEPOOP_SHOWSTATEMENT_H
#define DATABASEPOOP_SHOWSTATEMENT_H

#include "Database.h"
#include "regex"
#include "Statement.h"

#include <utility>


class ShowStatement : public Statement {

public:
    /**
    * @brief Constructor for ShowStatement class.
    * @param db A shared pointer to the Database object.
    * @param fullStatement The full SQL statement.
    */
    ShowStatement(std::shared_ptr<Database> db, std::string fullStatement);

    /**
     * @brief A test function to check the functionality of the ShowStatement class.
     * Prints a message indicating it's a show statement.
     */
    void test();

    /**
     * @brief Executes the SHOW statement.
     * Prints the tables in the database.
     */
    void execute();

    /**
     * @brief Parses a SHOW statement.
     * @param fullStatement The full SQL statement.
     * @param rest The remaining part of the statement.
     * @param db A shared pointer to the Database object.
     * @return A shared pointer to a Statement object representing the parsed SHOW statement.
     * @throws SyntaxError if there is a syntax error in the SQL statement.
     */
    static std::shared_ptr<Statement> parse(const std::string& fullStatement, const std::string& rest,
                                            const std::shared_ptr<Database>& db);



private:
    std::string tableName;

};

#endif //DATABASEPOOP_SHOWSTATEMENT_H
