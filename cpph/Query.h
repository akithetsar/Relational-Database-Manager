//
// Created by akith on 4/27/2024.
//

#ifndef DATABASEPOOP_QUERY_H
#define DATABASEPOOP_QUERY_H

#include <utility>
#include <vector>
#include <memory>
#include <regex>
#include <fstream>
#include <filesystem>

#include "Statement.h"
#include "Database.h"
#include "CreateStatement.h"
#include "DropStatement.h"
#include "InsertStatement.h"
#include "DeleteStatement.h"
#include "UpdateStatement.h"
#include "SelectStatement.h"
#include "ShowStatement.h"

#include "Condition.h"
#include "EqualCondition.h"
#include "NotEqualCondition.h"
#include "FileExceptions.h"
#include "SyntaxExceptions.h"

class Query {

public:
    /**
    * @brief Constructor for Query class.
    * @param db A shared pointer to a Database object.
    * @param fileText A constant reference to a string containing the file text.
    * @throws IncorrectFileType if the file type is incorrect.
    */
    Query(std::shared_ptr<Database> db, const std::string& fileText);

    /**
     * @brief Executes the parsed SQL statements.
     */
    void execute();

    /**
     * @brief Loads the contents of a query file.
     * @param filePath A constant reference to a string containing the file path.
     * @return A string containing the contents of the file.
     * @throws FileNotFoundException if the file is not found.
     */
    static std::string loadQueryFile(const std::string& filePath);

    /**
     * @brief Loads a query string from user input.
     * @return A string containing the user-entered query.
     */
    static std::string loadQueryString();

private:
    /**
     * @brief Parses the SQL queries from the file text.
     * @param fileText A constant reference to a string containing the file text.
     * @throws SyntaxError if there is a syntax error in the SQL statement.
     */
    void parseQuery(const std::string& fileText);

    /**
     * @brief Parses a single SQL statement.
     * @param statementPair A pair containing the statement type and its remaining part.
     * @return A shared pointer to a Statement object.
     * @throws SyntaxError if there is a syntax error in the SQL statement.
     */
    std::shared_ptr<Statement> parseStatement(const std::pair<std::string, std::string>& statementPair);

private:



    std::vector<std::shared_ptr<Statement>> statements;
    std::shared_ptr<Database> db;
};



#endif //DATABASEPOOP_QUERY_H
