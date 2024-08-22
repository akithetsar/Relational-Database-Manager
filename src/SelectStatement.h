//
// Created by akith on 5/4/2024.
//

#ifndef DATABASEPOOP_SELECTSTATEMENT_H
#define DATABASEPOOP_SELECTSTATEMENT_H

#include "Statement.h"
#include "EqualCondition.h"
#include "NotEqualCondition.h"
#include <utility>
#include "Filter.h"
#include "RuntimeErrorExceptions.h"

class SelectStatement : public Statement {

public:
    /**
      * @brief Constructor for SelectStatement class.
      * @param table The name of the table to select from.
      * @param selectors A vector of strings representing the selected columns.
      * @param filter The filter object containing conditions for filtering rows.
      * @param db A shared pointer to the Database object.
      * @param fullStatement The full SQL statement.
      */
    SelectStatement(std::string table, std::vector<std::string> selectors, Filter filter,
                    std::shared_ptr<Database> db, std::string fullStatement);

    /**
     * @brief Executes the SELECT statement.
     */
    void execute();

    /**
     * @brief Parses a SELECT statement.
     * @param fullStatement The full SQL statement.
     * @param rest The remaining part of the statement.
     * @param db A shared pointer to the Database object.
     * @return A shared pointer to a Statement object representing the parsed SELECT statement.
     * @throws SyntaxError if there is a syntax error in the SQL statement.
     */
    static std::shared_ptr<Statement> parse(const std::string& fullStatement, const std::string& rest,
                                            const std::shared_ptr<Database>& db);

    /**
     * @brief A test function to check the functionality of the SelectStatement class.
     * Prints the table name and the first selector.
     */
    void test();

private:
    std::string tableName;
    std::vector<std::string> selectors;
    Filter filter;


};

#endif //DATABASEPOOP_SELECTSTATEMENT_H
