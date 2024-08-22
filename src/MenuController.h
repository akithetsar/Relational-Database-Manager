//
// Created by akith on 4/20/2024.
//

#ifndef DATABASEPOOP_MENUCONTROLLER_H
#define DATABASEPOOP_MENUCONTROLLER_H

#include <stack>
#include <memory>

class Menu;
class MenuController {

    static MenuController *instance;

    std::shared_ptr<Menu> currentMenu;
    std::stack<std::shared_ptr<Menu>> menuStack;

    explicit MenuController(std::shared_ptr<Menu> startMenu);
public:
    static MenuController& getInstance(std::shared_ptr<Menu> startMenu);
    void start();


};


#endif //DATABASEPOOP_MENUCONTROLLER_H
