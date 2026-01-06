//
// Created by et118 on 12/16/25.
//
#include "../../include/Windows/Window.h"

Window::Window(const std::string& title, const WindowDimensions& windowDimensions, BorderRenderer* borderRenderer, const std::vector<MenuItem*> &menuItems) :
    windowDimensions(windowDimensions),
    borderRenderer(borderRenderer),
    menuItems(menuItems),
    mousePos(Vector2D<unsigned int>{0,0}),
    lastMouseDownPos(Vector2D<unsigned int>{0,0}),
    mouseButtonDown(Vector2D<bool>{false,false}),
    alive(true),
    focus(false),
    title(title)
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
    this->focus = hover;
}

bool Window::onMouseUp(unsigned int x, unsigned int y, bool rightClick) {
    /*Handle menuItems clicks*/
    if (rightClick) {
        this->mouseButtonDown.updateY(false); //Released rightclick
    } else {
        this->mouseButtonDown.updateX(false); //Released leftclick
    }
    if (!rightClick && y == 0) { //Check if we clicked on menu item
        unsigned int xOffset =
            this->windowDimensions.getMargin().getX() +
            this->windowDimensions.getBorderThickness().getX() +
            this->title.size();
        for (MenuItem* menuItem : this->menuItems) {
            if (x > xOffset && x < xOffset + menuItem->getTitle().size() + 2) {
                menuItem->click();
                return true; //Capture the click
            }
            xOffset += menuItem->getTitle().size() + 1;
        }
    }
    return false;
}

bool Window::onMouseDown(unsigned int x, unsigned int y, bool rightClick) {
    this->lastMouseDownPos.update(x,y);
    if (rightClick) {
        this->mouseButtonDown.updateY(true); //Pressed rightclick
    } else {
        this->mouseButtonDown.updateX(true); //Pressed leftclick
    }
    return false;
}

bool Window::onMouseMove(unsigned int x, unsigned int y) {
    this->mousePos.update(x,y);
    return false;
}

bool Window::onKeyboardInput(char key) {
    if (key == 127) { //delete key
        this->alive = false; //TODO temporary keyboard shortcut
        return true;
    }
    return false;
}

Content Window::render() {
    Content content = this->renderContent();
    if (this->borderRenderer != nullptr) {
        content = this->borderRenderer->encapsulateContent(content, this->title, this->menuItems, this->focus, this->windowDimensions, this->mousePos.getX(), this->mousePos.getY());
    }
    return content;
}
