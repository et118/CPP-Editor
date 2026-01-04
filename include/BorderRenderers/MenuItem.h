//
// Created by et118 on 12/17/25.
//

#ifndef CPP_EDITOR_MENUITEM_H
#define CPP_EDITOR_MENUITEM_H
#include <string>
#include <vector>
#include <utility>

#include "../Util/Content.h"

class MenuItem {
private:
    std::string title;
    void(*callback)(std::string);

public:
    MenuItem(const std::string &title, void(*callback)(std::string)) : title(title), callback(callback) {};

    std::string getTitle();
    void click();
};
#endif //CPP_EDITOR_MENUITEM_H