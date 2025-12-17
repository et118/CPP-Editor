//
// Created by et118 on 12/17/25.
//

#ifndef CPP_EDITOR_MENUITEM_H
#define CPP_EDITOR_MENUITEM_H
#include <string>
#include <vector>
#include <utility>
#include "../Util/Vector2D.h"
#include "../Util/Content.h"
class MenuItem {
private:
    std::string title;
    std::vector<std::pair<std::string, void(*)()>> dropDowns;
    unsigned int offset;

    unsigned int maxDropdownWidth;
    bool expanded;
public:
    MenuItem(unsigned int offset, unsigned int maxDropdownWidth);

    bool isExpanded();
    unsigned int getOffset();
    bool isPositionWithinBounds(unsigned int x, unsigned int y);
    void click(unsigned int x, unsigned int y);
};
#endif //CPP_EDITOR_MENUITEM_H