//
// Created by akith on 4/26/2024.
//

#ifndef DATABASEPOOP_STATEMENT_H
#define DATABASEPOOP_STATEMENT_H

#include <string>
#include <utility>
#include "Condition.h"
#include "NotEqualCondition.h"
#include "EqualCondition.h"
#include "SyntaxExceptions.h"
#include "RuntimeErrorExceptions.h"
#include "Record.h"
#include "Database.h"
#include <regex>


class Statement {

public:
    /**
     * @brief Constructor for Statement class.
     * @param db A shared pointer to a Database object.
     * @param fullStatement The full statement to be executed.
     */
    Statement(std::shared_ptr<Database> db, std::string fullStatement);

    /**
     * @brief Test function for Statement base class.
     */
    virtual void test();

    /**
     * @brief Executes the statement.
     */
    virtual void execute();

protected:
    std::shared_ptr<Database> db;
    static std::array<std::string, 16> keywords;
    std::string fullStatement;




    /**
     * @brief Checks if a word is an invalid keyword.
     * @param word The word to be checked.
     * @param fullStatement The full statement containing the word.
     * @throws SyntaxError if the word is an invalid keyword.
     */
    static void checkInvalidKeyword(const std::string& word, const std::string& fullStatement);

    /**
     * @brief Checks if a word matches a specified keyword.
     * @param word The word to be checked.
     * @param keyword The specified keyword.
     * @param fullStatement The full statement containing the word.
     * @throws SyntaxError if the word does not match the specified keyword.
     */
    static void checkForKeyword(const std::string& word, const std::string& keyword, const std::string& fullStatement);

    /**
     * @brief Checks the validity of a table name.
     * @param word The table name to be checked.
     * @param fullStatement The full statement containing the table name.
     * @throws SyntaxError if the table name contains invalid characters.
     */
    static void checkTableNameValidity(const std::string& word, const std::string& fullStatement);

    /**
     * @brief Checks the validity of a column name.
     * @param word The column name to be checked.
     * @param fullStatement The full statement containing the column name.
     * @return The validated column name.
     * @throws SyntaxError if the column name contains invalid characters.
     */
    static std::string checkColumnNameValidity(const std::string& word, const std::string& fullStatement);

    /**
     * @brief Checks the validity of a selector.
     * @param word The selector to be checked.
     * @param fullStatement The full statement containing the selector.
     * @return The validated selector.
     * @throws SyntaxError if the selector contains invalid characters.
     */
    static std::string checkSelectorNameValidity(const std::string& word, const std::string& fullStatement);

    /**
     * @brief Parses columns from a string.
     * @param columnsString The string containing columns.
     * @param fullStatement The full statement containing the columns.
     * @return A vector of parsed column names.
     * @throws SyntaxError if any column is an invalid keyword or contains invalid characters.
     */
    static std::vector<std::string> parseColumns(const std::string& columnsString, const std::string& fullStatement);

    /**
     * @brief Parses selectors from a string.
     * @param selectorsString The string containing selectors.
     * @param fullStatement The full statement containing the selectors.
     * @return A vector of parsed selectors.
     * @throws SyntaxError if any selector is an invalid keyword or contains invalid characters.
     */
    static std::vector<std::string> parseSelectors(const std::string& selectorsString, const std::string& fullStatement);

    /**
     * @brief Parses conditions from a string.
     * @param conditionsString The string containing conditions.
     * @param fullStatement The full statement containing the conditions.
     * @return A vector of parsed conditions.
     * @throws SyntaxError if any condition is written incorrectly.
     */
    static std::vector<std::shared_ptr<Condition>> parseConditions(const std::string& conditionsString, const std::string& fullStatement);

    /**
     * @brief Parses records from a string.
     * @param recordsString The string containing records.
     * @param fullStatement The full statement containing the records.
     * @return A vector of parsed records.
     * @throws SyntaxError if any record value is missing quotation marks.
     */
    static std::vector<Record> parseRecords(const std::string& recordsString, const std::string& fullStatement);

    /**
     * @brief Parses changes from a string.
     * @param changesString The string containing changes.
     * @param fullStatement The full statement containing the changes.
     * @return A vector of parsed changes.
     * @throws SyntaxError if any change is written incorrectly.
     */
    static std::vector<std::pair<std::string, std::string>> parseChanges(const std::string& changesString, const std::string& fullStatement);


};



#endif //DATABASEPOOP_STATEMENT_H
