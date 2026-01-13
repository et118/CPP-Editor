//
// Created by et118 on 12/17/25.
//

#ifndef CPP_EDITOR_MENUITEM_H
#define CPP_EDITOR_MENUITEM_H
#include <string>

class Window; //forward declaration because MenuItem is used in Window class :P

class MenuItem {
private:
    std::string title;
    Window* window;
    void(*callback)(Window*, std::string);

public:
    MenuItem(const std::string &title, Window* window, void(*callback)(Window*,std::string)) : title(title), window(window), callback(callback) {};
    std::string getTitle();
    void click() const;
};
#endif //CPP_EDITOR_MENUITEM_H