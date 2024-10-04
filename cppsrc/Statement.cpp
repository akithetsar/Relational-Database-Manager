//
// Created by akith on 5/9/2024.
//

#include "Statement.h"
std::array<std::string, 16> Statement::keywords = {"CREATE", "TABLE", "DROP", "SELECT", "FROM",
                                                   "WHERE", "INNER", "JOIN", "INSERT", "INTO", "VALUES", "UPDATE",
                                                   "SET",
                                                   "SHOW", "TABLES", "AND"};

Statement::Statement(std::shared_ptr <Database> db, std::string fullStatement) : db(std::move(db)), fullStatement(std::move(fullStatement)) {}

void Statement::test() { std::cout << "Statement base class"; }

void Statement::execute() {}

void Statement::checkInvalidKeyword(const std::string &word, const std::string &fullStatement) {
    if (std::find(keywords.begin(), keywords.end(), word) != keywords.end()) {
        throw SyntaxError("Syntax Error: Invalid use of keyword " + word + " at: " + fullStatement);
    }
}

void Statement::checkForKeyword(const std::string &word, const std::string &keyword, const std::string &fullStatement) {
    if (word != keyword) {
        throw SyntaxError("Missing " + keyword + " keyword at " + fullStatement);
    }
}

void Statement::checkTableNameValidity(const std::string &word, const std::string &fullStatement) {
    std::smatch match;
    if (!std::regex_match(word, match, std::regex("\\s*([A-Za-z]+)\\s*"))) {
        throw SyntaxError("table_name contains a non-alphabet letter at: " + fullStatement);
    }
}

std::string Statement::checkColumnNameValidity(const std::string &word, const std::string &fullStatement) {
    std::smatch match;
    if (!std::regex_match(word, match, std::regex("\\s*(\\w+)\\s*"))) {
        throw SyntaxError("Column tableName contains invalid character at: " + fullStatement);
    } else return match[1];
}

std::string Statement::checkSelectorNameValidity(const std::string &word, const std::string &fullStatement) {
    std::smatch match;
    if (!std::regex_match(word, match, std::regex("\\s*(\\s*(?:\\w+)\\s*|\\s*(?:\\*)\\s*)\\s*"))) {
        throw SyntaxError("Selector " + word +" contains invalid character at: " + fullStatement);
    } else return match[1];
}

std::vector <std::string> Statement::parseColumns(const std::string &columnsString, const std::string &fullStatement) {
    std::string column;
    std::stringstream ss(columnsString);
    std::vector<std::string> columns;

    while (std::getline(ss, column, ',')) {

        checkInvalidKeyword(column, fullStatement);
        columns.push_back(checkColumnNameValidity(column, fullStatement));
    }

    return columns;
}

std::vector <std::string>
Statement::parseSelectors(const std::string &selectorsString, const std::string &fullStatement) {
    std::string selector;
    std::stringstream ss(selectorsString);
    std::vector<std::string> selectors;

    while (std::getline(ss, selector, ',')) {
        checkInvalidKeyword(selector, fullStatement);
        std::smatch submatch;
        std::regex_match(selector, submatch, std::regex("\\s*[\\w*]+\\s*"));
        selectors.push_back(checkSelectorNameValidity(submatch.str(), fullStatement));
    }

    return selectors;
}

std::vector <std::shared_ptr<Condition>>
Statement::parseConditions(const std::string &conditionsString, const std::string &fullStatement) {
    std::vector<std::shared_ptr<Condition>> conditions;
    std::smatch conditionMatch;
    std::smatch columnValuePair;
    std::string::const_iterator conditionsStart(conditionsString.cbegin());

    while (std::regex_search(conditionsStart, conditionsString.cend(), conditionMatch,
                             std::regex(
                                     "\\s*([\\w]*\\s*=\\s*[\\w\'\"]*)|([\\w]*\\s*(?:<>|!=)\\s*[\\w\'\"]*)\\s*"))) {

        std::string conditionsMatchString = conditionMatch[0].str();
        if (std::regex_match(conditionsMatchString, columnValuePair,
                             std::regex("\\s*([\\w]*)\\s*=\\s*(?:\"([\\w]+)\"|'([\\w]+)')\\s*"))) {
            conditions.push_back(
                    std::make_shared<EqualCondition>(columnValuePair[1], columnValuePair[2]));
        } else if (std::regex_match(conditionsMatchString, columnValuePair,
                                    std::regex(
                                            "\\s*([\\w]*)\\s*(?:<>|!=)\\s*(?:\"([\\w]+)\"|'([\\w]+)')\\s*"))) {
            conditions.push_back(
                    std::make_shared<NotEqualCondition>(columnValuePair[1], columnValuePair[2]));
        } else {
            throw SyntaxError("Condition written incorrectly at: " + fullStatement);
        }

        conditionsStart = conditionMatch.suffix().first;
    }

    return conditions;
}

std::vector <Record> Statement::parseRecords(const std::string &recordsString, const std::string &fullStatement) {
    std::string value;
    std::smatch recordsMatch;
    std::smatch submatch;
    std::vector<Record> records;

    std::string::const_iterator searchStart(recordsString.cbegin());
    while (std::regex_search(searchStart, recordsString.cend(), recordsMatch,
                             std::regex("\\s*\\(([\",\\w\\s\']*)\\)"))) {

        std::vector<std::string> newRecord;
        std::smatch noParantesis;
        std::string test = recordsMatch[1].str();
        std::regex_match(test, noParantesis, std::regex("\\s*([\",\\w\\s\']+)\\s*"));
        std::stringstream recordStream(noParantesis[1]);
        while (std::getline(recordStream, value, ',')) {
            if (!std::regex_match(value, submatch,
                                  std::regex("\\s*(?:\"([\\w]+)\"|\'([\\w]+)\')\\s*"))) {
                throw SyntaxError("Value missing \"\" at " + fullStatement);
            } else {
                newRecord.push_back(submatch[1]);
            }

        }
        records.push_back(Record(newRecord));
        searchStart = recordsMatch.suffix().first;
    }
    return records;
}

std::vector <std::pair<std::string, std::string>>
Statement::parseChanges(const std::string &changesString, const std::string &fullStatement) {
    std::vector<std::pair<std::string, std::string>> changes;
    std::smatch conditionMatch;
    std::smatch columnValuePair;
    std::string::const_iterator searchStart(changesString.cbegin());
    while (std::regex_search(searchStart, changesString.cend(), conditionMatch,
                             std::regex("\\s*([\\w]*\\s*=\\s*[\\w\'\"]*)\\s*"))) {

        std::string conditionsMatchString = conditionMatch[1].str();
        if (std::regex_match(conditionsMatchString, columnValuePair,
                             std::regex("\\s*([\\w]*)\\s*=\\s*(?:\"([\\w]+)\"|'([\\w]+)')\\s*"))) {
            changes.push_back(
                    std::make_pair<std::string, std::string>(columnValuePair[1], columnValuePair[2]));
        } else {
            throw SyntaxError("Condition written incorrectly at: " + fullStatement);
        }

        searchStart = conditionMatch.suffix().first;
    }
    return changes;
}
