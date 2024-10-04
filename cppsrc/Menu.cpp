//
// Created by akith on 4/20/2024.
//

#include "Menu.h"
#include "MenuController.h"
#include <unistd.h>
#include "MenuExceptions.h"
#include <string>

Menu::Menu(const std::vector<Menu::MenuOption> &options, std::string menuHeader) : menuOptions(options),
                                                                                   menuHeader(menuHeader) {}


std::shared_ptr<Menu> Menu::runOption(char choice) {

    for (auto &item: menuOptions) {
        if (item.num == choice) {

            if (item.subMenu != nullptr) {
                return item.subMenu;
            } else {

                item.function();
                return nullptr;

            }

        }
    }

    throw InvalidMenuChoiceException(
            "Invalid menu choice: " + std::string(1, choice) + ". Please try a given choice");


}


void Menu::displayMenu() {
    std::cout << menuHeader << std::endl;
    for (auto &option: menuOptions) {
        std::cout << option.num << ". " << option.text << std::endl;
    }
}
