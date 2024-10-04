//
// Created by akith on 5/1/2024.
//

#ifndef DATABASEPOOP_DELETESTATEMENT_H
#define DATABASEPOOP_DELETESTATEMENT_H


#include "Statement.h"
#include "Filter.h"
#include <utility>
#include <vector>
#include <memory>

class DeleteStatement : public Statement {

public:

    /**
        * @brief Constructs a DeleteStatement object.
        *
        * @param tableName The name of the table from which records are to be deleted.
        * @param filter The filter containing conditions for record deletion.
        * @param db Pointer to the database.
        * @param fullStatement The full DELETE SQL statement.
        */
    DeleteStatement(std::string tableName, Filter filter, std::shared_ptr<Database> db, std::string fullStatement);

    /**
     * @brief Tests the DeleteStatement object.
     *
     * Prints information about the delete statement.
     */
    void test();

    /**
     * @brief Executes the delete statement.
     *
     * Deletes records from the specified table based on the provided conditions.
     * Throws an exception if an error occurs during execution.
     */
    void execute();

    /**
     * @brief Parses a DELETE SQL statement.
     *
     * @param fullStatement The full DELETE SQL statement.
     * @param rest The portion of the statement excluding the initial keyword "DELETE".
     * @param db Pointer to the database.
     * @return A shared pointer to the parsed DeleteStatement object.
     * @throws SyntaxError if there is a syntax error in the SQL statement.
     */
    static std::shared_ptr<Statement> parse(const std::string& fullStatement, const std::string& rest,
                                            const std::shared_ptr<Database>& db);

private:
    std::string tableName;
    Filter filter;
};


#endif //DATABASEPOOP_DELETESTATEMENT_H
