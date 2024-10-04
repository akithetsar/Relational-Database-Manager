//
// Created by akith on 4/20/2024.
//

#include <limits>
#include "MenuController.h"
#include "Menu.h"

MenuController *MenuController::instance = nullptr;

MenuController &MenuController::getInstance(std::shared_ptr<Menu> startMenu) {
    if (instance == nullptr) {
        instance = new MenuController(std::move(startMenu));
    }
    return *instance;
}


MenuController::MenuController(std::shared_ptr<Menu> startMenu) : menuStack(std::stack<std::shared_ptr<Menu>>()) {

    if (startMenu) {
        currentMenu = std::move(startMenu);  // Move ownership to currentMenu
        menuStack.push(currentMenu);  // Push to menuStack
    } else {
        std::cout << "Error: startMenu is null!" << std::endl;
    }
}


void MenuController::start() {
    char choice;
    while (currentMenu != nullptr) {
        try {
            currentMenu->displayMenu();

            std::cout << (menuStack.size() == 1 ? "Enter your choice (or 'q' to quit): "
                                                : "Enter your choice (or 'q' to return): ");
            std::cin >> choice;
            if (choice == 'q') {
                menuStack.pop();
                if (!menuStack.empty()) currentMenu = menuStack.top();
                else currentMenu = nullptr;
                system("clear");
            } else {
                system("clear");
                std::shared_ptr<Menu> subMenu = currentMenu->runOption(choice);
                if (subMenu != nullptr) {
                    menuStack.push(subMenu);
                    currentMenu = menuStack.top();
                } else {
                    if (menuStack.size() != 1) {
                        menuStack.pop();
                        currentMenu = menuStack.top();
                    }
                }

            }


        }
        catch (std::exception &exception) {
            std::cout << exception.what() << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cout << "Click Enter to leave..." << std::endl;
            getchar();
            system("clear");

        }


    }

}




