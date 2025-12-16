//
// Created by et118 on 12/16/25.
//
#include "../../include/Windows/Window.h"

Window::Window(std::string &title, WindowDimensions &windowDimensions, BorderRenderer *borderRenderer, std::vector<MenuItem *> &menuItems) {
    this->title = title;
    this->hovered = false;
    this->alive = true;
    this->windowDimensions = windowDimensions;
    this->borderRenderer = borderRenderer;
    this->menuItems = menuItems;
}

Window::~Window() {
    delete this->borderRenderer;
    for (MenuItem* menuItem : this->menuItems) {
        delete menuItem;
    }
    this->menuItems.clear();
}

bool Window::isAlive() {
    return this->alive;
}

void Window::setHovered(bool hover) {
    this->hovered = hover;
}

bool Window::onMouseClick(unsigned int x, unsigned int y, bool rightClick) {
    /*Handle menuItems clicks*/
    for (MenuItem* menuItem : this->menuItems) {
        if (menuItem->isPositionWithinArea(x, y)) {
            menuItem->run();
            return true;
        }
    }
    return false;
}

bool Window::onKeyboardInput(char key) {
    if (key == 127) { //delete key
        this->alive = false;
        return true;
    }
    return false;
}

Content Window::render() {
    Content content = this->renderContent();
    if (this->borderRenderer != nullptr) {
        content = this->borderRenderer->encapsulateContent(content, this->title, this->hovered, this->windowDimensions);
    }
    return content;
}
