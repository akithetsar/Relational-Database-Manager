//
// Created by akith on 5/9/2024.
//

#include "Format.h"
std::shared_ptr <Database> Format::loadDatabase(const std::string &filePath) {

    std::smatch match;
    // Open the file for reading
    std::ifstream infile(filePath);
    if(!std::regex_match(filePath, match, std::regex(".+\\\\(.+)\\.customSQL"))){
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


    std::stringstream ss(fileContents);
    std::string section;
    std::string queryText;
    while (std::getline(ss, section, '%')) {
        std::regex_match(section, match, std::regex("\\s*([\\w\\s]+):\\n([\\w\\n|(),;\"\']*)\\s*"));
        if(match[1] == "CREATE TABLE"){

            std::smatch submatch;
            std::string argumentsString = match[2];
            std::string::const_iterator searchStart2(argumentsString.cbegin());
            while (std::regex_search(searchStart2, argumentsString.cend(), submatch,
                                     std::regex(
                                             "\\s*([\\w]*)\\|(\\([\\w,]*\\));\\s*"))) {
                queryText += "CREATE TABLE ";
                queryText += submatch[1].str() + " " + submatch[2].str() + "\n;";

                searchStart2 = submatch.suffix().first;
            }
        }
        else if(match[1] == "INSERT INTO"){
            std::smatch submatch;
            std::string argumentsString = match[2];
            std::string::const_iterator searchStart2(argumentsString.cbegin());
            while (std::regex_search(searchStart2, argumentsString.cend(), submatch,
                                     std::regex(
                                             "\\s*([\\w]+)\\|(\\([\\w,()]+\\))\\|(\\([\\w'\",]+\\));\\s**"))) {
                queryText += "INSERT INTO ";
                queryText += submatch[1].str() + " " + submatch[2].str() + " VALUES " + submatch[3].str() + "\n;";

                searchStart2 = submatch.suffix().first;
            }
        }
        else{
            throw IncorrectFileFormat(filePath);
        }
    }
    Query createQuery(db, queryText);
    createQuery.execute();
    db->setFilePath(filePath);
    return db;
}

void Format::exportDatabaseToSql(const std::string &filePath, const std::shared_ptr <Database> &db) {



    std::smatch match;
    // Open the file for reading

    // Check if the file is opened successfully
    std::string path = filePath + db->getName() + ".sql";
    std::ofstream outfile(path, std::ios::trunc);

    if (!outfile) {
        throw FileNotFoundException("File " + filePath + " not found");
    }

    //Creates
    for (const auto &tablePair: db->getTables()) {
        outfile << "CREATE TABLE " + tablePair.first + " (";
        for (int i = 0; i < tablePair.second.getColumns().size(); i++) {
            outfile << '\n' + tablePair.second.getColumns()[i] + '\t' + "VARCHAR(50)";
            if (i != tablePair.second.getColumns().size() - 1) outfile << ',';
        }
        outfile << "\n);\n";
    }

    //Inserts

    for (const auto &tablePair: db->getTables()) {
        std::string prefix;
        prefix += "INSERT INTO " + tablePair.first + '(';

        for (int i = 0; i < tablePair.second.getColumns().size(); i++) {
            prefix += tablePair.second.getColumns()[i];
            if (i != tablePair.second.getColumns().size() - 1) prefix += ',';
        }
        prefix += ") VALUES(";
        std::string fullStatement;
        for (const auto &record: tablePair.second.getRecords()) {
            fullStatement = prefix;
            for (int i = 0; i < record.getData().size(); i++) {
                fullStatement += '\'' + record.getData()[i] + '\'';
                if (i != record.getData().size() - 1) fullStatement += ',';
            }
            fullStatement += ");\n";
            outfile << fullStatement;
        }

    }




}

void Format::exportDatabaseToCustom(const std::string &filePath, const std::shared_ptr <Database> &db) {


    std::smatch match;
    // Open the file for reading
    std::string path = filePath;
    // Check if the file is opened successfully

    std::ofstream outfile(path, std::ios::out | std::ios::trunc);


    outfile << "CREATE TABLE:\n";
    //CREATE:
    //nazivTabele|(kol1,kol2...)
    //...
    for (const auto &tablePair: db->getTables()) {
        outfile << tablePair.first << "|(";
        for (int i = 0; i < tablePair.second.getColumns().size(); i++) {
            outfile << tablePair.second.getColumns()[i];
            if (i != tablePair.second.getColumns().size() - 1) outfile << ',';
        }
        outfile << ");\n";
    }
    outfile << "%\n";
    //INSERT INTO:
    //nazivTabele|(kol1, kol2, kol3, ...)|(vrednost1, vrednost2, vrednost3, ...)
    //...
    outfile << "INSERT INTO:\n";
    for (const auto &tablePair: db->getTables()) {

        std::string prefix;
        prefix += tablePair.first + "|(";

        for (int i = 0; i < tablePair.second.getColumns().size(); i++) {
            prefix += tablePair.second.getColumns()[i];
            if (i != tablePair.second.getColumns().size() - 1) prefix += ',';
        }
        prefix += ")|(";
        std::string fullStatement;
        for (const auto &record: tablePair.second.getRecords()) {
            fullStatement = prefix;
            for (int i = 0; i < record.getData().size(); i++) {
                fullStatement += '\"' + record.getData()[i] + '\"';
                if (i != record.getData().size() - 1) fullStatement += ',';
            }
            fullStatement += ");\n";
            outfile << fullStatement;
        }

    }
}
