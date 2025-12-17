//
// Created by et118 on 12/16/25.
//
#include "../../include/Windows/Window.h"

Window::Window(std::string& title, WindowDimensions& windowDimensions, BorderRenderer* borderRenderer, std::vector<MenuItem*> &menuItems) :
    windowDimensions(windowDimensions),
    borderRenderer(borderRenderer),
    menuItems(menuItems),
    mousePos(Vector2D<unsigned int>{0,0}),
    lastMouseDownPos(Vector2D<unsigned int>{0,0}),
    mouseButtonDown(Vector2D<bool>{false,false}),
    alive(true),
    hovered(false),
    title(this->title)
{};

Window::~Window() {
    delete this->borderRenderer; /*Even though we don't own it, lets make sure its deleted incase subclass forgets*/
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

bool Window::onMouseUp(unsigned int x, unsigned int y, bool rightClick) {
    /*Handle menuItems clicks*/
    if (!rightClick) {
        this->mouseButtonDown.updateX(false);
    } else {
        this->mouseButtonDown.updateY(false);
    }
    if (!rightClick) {
        unsigned int xOffset = this->title.size();
        for (MenuItem* menuItem : this->menuItems) {
            xOffset += menuItem->getOffset();
            if (x < xOffset) continue;
            unsigned int relativeX = x - xOffset;
            if (menuItem->isPositionWithinBounds(relativeX, y)) {
                menuItem->click(relativeX, y);
                return true;
            }
        }
    }
    return false;
}

bool Window::onMouseDown(unsigned int x, unsigned int y, bool rightClick) {
    this->lastMouseDownPos.update(x,y);
    if (!rightClick) {
        this->mouseButtonDown.updateX(true);
    } else {
        this->mouseButtonDown.updateY(true);
    }
    return false;
}

bool Window::onMouseMove(unsigned int x, unsigned int y) {
    this->mousePos.update(x,y);
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
        content = this->borderRenderer->encapsulateContent(content, this->title, this->menuItems, this->hovered, this->windowDimensions, this->mousePos.getX(), this->mousePos.getY());
        /*TO BE ADDED INSIDE ENCAPSULATECONTENT: for (MenuItem* menuItem : this->menuItems) {
            if (menuItem->isExpanded()) {
                Content dropdown = menuItem->getDropdown();
            }
        }*/
    }
    return content;
}
