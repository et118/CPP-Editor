//
// Created by et118 on 12/17/25.
//
#include "../../include/BorderRenderers/MenuItem.h"

std::string MenuItem::getTitle() {
    return this->title;
}

void MenuItem::click() const {
    this->callback(this->window,this->title);
}
