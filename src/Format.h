//
// Created by akith on 4/25/2024.
//

#ifndef DATABASEPOOP_FORMAT_H
#define DATABASEPOOP_FORMAT_H

#include "Database.h"
#include <regex>
#include <fstream>
#include <filesystem>
#include "FileExceptions.h"
#include "Query.h"

class Format {

public:

    /**
      * @brief Load a database from a custom SQL file.
      *
      * @param filePath The path to the custom SQL file.
      * @return A shared pointer to the loaded Database.
      * @throws IncorrectFileType if the file extension is not '.customSQL'.
      * @throws FileNotFoundException if the file is not found.
      * @throws IncorrectFileFormat if the file format is incorrect.
      */
    static std::shared_ptr<Database> loadDatabase(const std::string& filePath);

    /**
     * @brief Export the database to an SQL file.
     *
     * @param filePath The path to the output SQL file.
     * @param db A shared pointer to the Database to be exported.
     * @throws FileNotFoundException if the file is not found.
     */
    static void exportDatabaseToSql(const std::string& filePath, const std::shared_ptr<Database>& db);

    /**
     * @brief Export the database to a custom SQL file.
     *
     * @param filePath The path to the output custom SQL file.
     * @param db A shared pointer to the Database to be exported.
     */
    static void exportDatabaseToCustom(const std::string& filePath, const std::shared_ptr<Database>& db);
};





#endif //DATABASEPOOP_FORMAT_H
