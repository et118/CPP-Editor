//
// Created by et118 on 12/17/25.
//
#include "../../include/BorderRenderers/MenuItem.h"

MenuItem::MenuItem(unsigned int offset, unsigned int maxDropdownWidth) :
    offset(offset),
    maxDropdownWidth(maxDropdownWidth){}

bool MenuItem::isExpanded() {
    return this->expanded;
}

unsigned int MenuItem::getOffset() {
    return this->offset;
}

bool MenuItem::isPositionWithinBounds(unsigned int x, unsigned int y) {
    if (x < title.size() && y == 0) return true;
    if (this->expanded) {
        if (x < this->maxDropdownWidth && y < this->dropDowns.size()) return true;
    }

    return false;
}

void MenuItem::click(unsigned int x, unsigned int y) {
    size_t index = 0;
    for (std::pair<std::string, void(*)()> pair : this->dropDowns) {
        if (x < this->maxDropdownWidth && y > );

        index++;
    }
}

