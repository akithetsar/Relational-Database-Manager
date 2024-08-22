//
// Created by akith on 5/9/2024.
//

#include <fstream>
#include "SelectStatement.h"
SelectStatement::SelectStatement(std::string table, std::vector <std::string> selectors, Filter filter,
                                 std::shared_ptr <Database> db, std::string fullStatement)
        : Statement(std::move(db), std::move(fullStatement)), tableName(std::move(table)), selectors(std::move(selectors)),
          filter(std::move(filter)) {}

void SelectStatement::test() { std::cout << "Select statement: " << tableName << ' ' << selectors[0] << std::endl; }

void SelectStatement::execute() {


    std::vector<int> indices = filter.filterOut(db->getTable(tableName));
    std::vector<std::string> expandedSelectors;
    Table &table = db->getTable(tableName);
    Table selectedTable;
    std::smatch match;
    for (const auto &selector: selectors) {
        std::regex_match(selector, match, std::regex("\\s*([\\w]+|\\*)\\s*"));
        if (match[1].str() == "*") {

            for (const auto &column: table.getColumns()) {
                expandedSelectors.push_back(column);
            }
        } else {
            if (std::find(table.getColumns().begin(), table.getColumns().end(), match[1].str()) ==
                table.getColumns().end())
                throw RuntimeError(
                        "Selector " + selector + "not found in table " + table.getName() + " at statement: " +
                        fullStatement);
            expandedSelectors.push_back(match[1].str());
        }
    }

    selectedTable = table.createSubsetTable(expandedSelectors, indices);
    std::cout << selectedTable;
//    int buffer;
//    std::cin >> buffer;

}

std::shared_ptr <Statement>
SelectStatement::parse(const std::string &fullStatement, const std::string &rest, const std::shared_ptr <Database> &db) {

    std::smatch match;
    std::string tableName;
    std::vector<std::string> selectors;
    std::vector<std::shared_ptr<Condition>> conditions;
    std::smatch joinMatch;
    std::smatch whereMatch;
    if (std::regex_match(rest, match,
                         std::regex("\\s*([\\w*,\\s]+)\\s+(FROM)\\s+([\\w]+)\\s*(?:INNER JOIN\\s+([^(?WHERE)]+))?\\s+(?:WHERE\\s+([\\w=\\s\"',]+))?\\s*"))) {

        std::smatch submatch;
        tableName = match[3];

        //check errors
        checkForKeyword(match[2].str(), "FROM", fullStatement);
        checkInvalidKeyword(match[3].str(), fullStatement);
        checkTableNameValidity(tableName, fullStatement);

        //parse selectors
        selectors = SelectStatement::parseSelectors(match[1].str(), fullStatement);


        //parse conditions

        if (rest.find("WHERE") != std::string::npos) {
            // "WHERE" exists in the string
            conditions = Statement::parseConditions(match[5].str(), fullStatement);
        }

        return std::make_shared<SelectStatement>(tableName, selectors, Filter(conditions), db, fullStatement);

    } else {
        throw SyntaxError("Syntax Error at: " + fullStatement);
    }
}
