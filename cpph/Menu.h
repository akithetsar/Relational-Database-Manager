//
// Created by akith on 4/19/2024.
//

#ifndef DATABASEPOOP_MENU_H
#define DATABASEPOOP_MENU_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <memory>

class MenuController;

class Menu{

public:
    using MenuOptionFunction = std::function<void()>;
    struct MenuOption {
        char num;
        std::string text;

        std::shared_ptr<Menu> subMenu;
        MenuOptionFunction function;

        MenuOption(const MenuOption& other)
                : num(other.num),
                  text(other.text),
                  subMenu(other.subMenu ? std::make_shared<Menu>(*other.subMenu) : nullptr),
                  function(other.function) {}

        MenuOption(char num, std::string  text, MenuOptionFunction func, std::shared_ptr<Menu> submenu = nullptr)
                : num(num),
                  text(std::move(text)),
                  function(std::move(func)),
                  subMenu(std::move(submenu)) {}
    };

    explicit Menu(const std::vector<MenuOption>& options, std::string menuHeader);


    std::shared_ptr<Menu> runOption(char choice);



    void displayMenu();




private:
    std::vector<MenuOption> menuOptions;
    std::string menuHeader;

};


#endif //DATABASEPOOP_MENU_H
