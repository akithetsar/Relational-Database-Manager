//
// Created by akith on 5/9/2024.
//

#include "Query.h"
Query::Query(std::shared_ptr <Database> db, const std::string &fileText) : db(std::move(db)) {

    parseQuery(fileText);

}

void Query::execute() {

    for (auto &statement: statements) {
        statement->execute();
    }


}

std::string Query::loadQueryFile(const std::string &filePath) {
    std::smatch match;
    // Open the file for reading
    std::ifstream infile(filePath);
    if(!std::regex_match(filePath, match, std::regex(".+\\\\(.+)*\\.txt"))){
        throw IncorrectFileType(filePath);
    }
    std::shared_ptr<Database> db = std::make_shared<Database>(match[1]);
    // Check if the file is opened successfully
    if (!infile) {
        throw FileNotFoundException("File " + filePath + " not found");
    }

    // Read the contents of the file into a string
    std::string fileContents((std::istreambuf_iterator<char>(infile)),
                             std::istreambuf_iterator<char>());

    // Close the file
    infile.close();




    return fileContents;
}

std::string Query::loadQueryString() {
    std::string queryText;
    std::cout << "Enter query string: " << std::endl;
    std::cin >> queryText;
    return queryText;
}

void Query::parseQuery(const std::string &fileText) {

    // Vector to store pairs of statement and its remaining part
    std::vector<std::pair<std::string, std::string>> statementPairs;

    // Regular expression to validate SQL statements
    std::regex isValidStatement(
            "\\s*(CREATE|DROP|SELECT|INSERT|UPDATE|DELETE|SHOW)\\s*([(),\"\\w\\s\'=<>*]*)\\s*");

    // Stringstream to process input text
    std::stringstream ss(fileText);
    std::vector<std::string> parts;
    std::string temp;

//        // Split the input text by semicolon

    std::string::const_iterator queryStart(fileText.cbegin());
    std::smatch statementMatch;
    while (std::regex_search(queryStart, fileText.cend(), statementMatch,
                             std::regex(
                                     "\\s*([^;.]+);\\s*"))) {

        std::string statement, other;

        // Check if the extracted substring is a valid SQL statement
        std::smatch match;
        temp = statementMatch[1].str();
        if (std::regex_match(temp, match, isValidStatement)) {
            statement = match[1]; // Extract the statement type
            other = match[2];     // Extract the remaining part of the statement
        } else {
            // If the statement is not valid, throw an error
            std::smatch invalidStatement;
            std::regex_search(temp, invalidStatement, std::regex("\\s*([\\w]*)\\s{1}.*"));
            throw SyntaxError("SYNTAX ERROR at: " + invalidStatement[1].str() + " is not a valid statement");
        }

        // Parse and store the statement pair
        statements.push_back(parseStatement(std::make_pair(statement, other)));
        queryStart = statementMatch.suffix().first;
    }
}

std::shared_ptr <Statement> Query::parseStatement(const std::pair <std::string, std::string> &statementPair) {

    std::string statement = statementPair.first;
    std::string rest = statementPair.second;
    std::string fullStatement = statement + ' ' + rest;
    std::smatch match;
    if (statement == "CREATE") {
        return CreateStatement::parse(fullStatement, rest, db);

    } else if (statement == "DROP") {
        return DropStatement::parse(fullStatement, rest, db);

    } else if (statement == "SELECT") {
        return SelectStatement::parse(fullStatement, rest, db);
    } else if (statement == "INSERT") {
        return InsertStatement::parse(fullStatement, rest, db);

    } else if (statement == "UPDATE") {
        return UpdateStatement::parse(fullStatement, rest, db);
    } else if (statement == "DELETE") {
        return DeleteStatement::parse(fullStatement, rest, db);

    } else if (statement == "SHOW") {
        return ShowStatement::parse(fullStatement, rest, db);
    } else {
        throw SyntaxError("SYNTAX ERROR at: " + statement + " is not a valid statement");
    }
}
