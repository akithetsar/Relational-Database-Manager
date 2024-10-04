#include <iostream>


#include "Database.h"
#include "Menu.h"
#include "MenuController.h"
#include "Table.h"
#include "Query.h"
#include "Format.h"
#include "MenuExceptions.h"




std::shared_ptr<Database> createDatabase() {
    std::cout << "Enter the name of the database: ";
    std::string name;
    std::cin >> name;
    return std::make_shared<Database>(name);
}

void save(const std::shared_ptr<Database> &currDb) {
    if (currDb == nullptr)
        throw DatabaseNotLoadedException();
    if (!currDb->isChanged()) {
        std::cout << "Database is already saved!";
    } else {
        if (currDb->getFilePath() == nullptr) {

            std::cout << "Enter the path where to export the file: ";
            std::string path;
            std::cin >> path;
            Format::exportDatabaseToCustom(path, currDb);
        } else {
            Format::exportDatabaseToCustom(*currDb->getFilePath(), currDb);
        }
    }
}


int main() {


    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Welcome to the database simulator" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    std::cout << "Click Enter...";
    getchar();
    system("clear");


    std::shared_ptr<Database> currDb;
    currDb = std::make_shared<Database>("virtualDb");
    std::vector<Menu::MenuOption> queryInputOptions = {
            {'1', "Text File", [&currDb] {
                if (currDb == nullptr) throw DatabaseNotLoadedException();
                Database old = *currDb;
                try {
                    std::string path;
                    std::cout << "Enter query path: ";
                    std::cin >> path;
                    currDb->executeQuery(currDb, path);
                }
                catch (const std::exception &exception) {
                    currDb = std::make_shared<Database>(old);
                    std::cout << exception.what();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                    std::cout << "Click Enter to leave..." << std::endl;
                    getchar();
                    system("clear");
                }
            }},
            {'2', "String",    [&currDb] {
                if (currDb == nullptr) throw DatabaseNotLoadedException();
                currDb->executeQuery(currDb, Query::loadQueryString());

            }}
    };

    std::vector<Menu::MenuOption> exportFileOptions = {
            {'1', "SQL Format",    [&currDb] {
                if (currDb == nullptr)
                    throw DatabaseNotLoadedException();
                std::cout << "Enter the path where to export the file: ";
                std::string path;
                std::cin >> path;
                Format::exportDatabaseToSql(path, currDb);
            }},
            {'2', "Custom Format", [&currDb] {
                if (currDb == nullptr)
                    throw DatabaseNotLoadedException();
                std::string path;
                std::cout << "Enter the path where to export the file: ";
                std::string filePath;
                std::cin >> filePath;
                path = filePath + currDb->getName() + ".customSQL";


                Format::exportDatabaseToCustom(path, currDb);
            }}
    };

// Manually set the subMenu pointers to create the submenu structure


    std::vector<Menu::MenuOption> mainMenuOptions = {
            {'1', "Create New Database",      [&currDb]() {
                currDb = createDatabase();
                Database old = *currDb;

            }},
            {'2', "Upload Existing Database", [&currDb] {
                std::cout << "Enter file path: ";
                std::string path;
                std::cin >> path;
                currDb = Format::loadDatabase(path);
            }},
            {'3', "Execute Query",            nullptr, std::make_shared<Menu>(queryInputOptions,
                                                                              "Choose query input")},
            {'4', "Show Database",            [&currDb] {
                if (currDb == nullptr)
                    throw DatabaseNotLoadedException();
                std::cout << *currDb;
            }},
            {'5', "Export Database",          nullptr, std::make_shared<Menu>(exportFileOptions,
                                                                              "Choose query input")},
            {'6', "Save Database",            [&currDb] {


            }}


    };


    std::shared_ptr<Menu> mainMenu = std::make_shared<Menu>(mainMenuOptions, "MainMenu");
    MenuController &menuController{MenuController::getInstance(mainMenu)};
    menuController.start();

    if (currDb->isChanged() && currDb) {
        if (currDb == nullptr)
            throw DatabaseNotLoadedException();
        if (!currDb->isChanged()) {
            std::cout << "Database is already saved!";
        } else {
            if (currDb->getFilePath() == nullptr) {

                std::cout << "Enter the path where to export the file: ";
                std::string path;
                std::cin >> path;
                Format::exportDatabaseToCustom(path, currDb);
            } else {
                Format::exportDatabaseToCustom(*currDb->getFilePath(), currDb);
            }
        }
    }

    return 0;
}



