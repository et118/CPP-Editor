//
// Created by et118 on 12/16/25.
//
#include "../../include/Windows/Window.h"

Window::Window(const std::string& title, const WindowDimensions& windowDimensions, BorderRenderer* borderRenderer, const std::vector<MenuItem*> &menuItems) :
    windowDimensions(windowDimensions),
    borderRenderer(borderRenderer),
    menuItems(menuItems),
    currentMousePos(Vector2D<unsigned int>{0,0}),
    lastMousePos(Vector2D<unsigned int>{0,0}),
    lastMouseDownPos(Vector2D<unsigned int>{0,0}),
    mouseButtonState(Vector2D<bool>{false,false}),
    wasMouseButtonClicked(Vector2D<bool>{false,false}),
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

bool Window::isAlive() const {
    return this->alive;
}

void Window::setFocused(bool focused) {
    this->focus = focused;
}

bool Window::onMouseUp(unsigned int x, unsigned int y, bool rightClick) {
    /*Handle menuItems clicks*/
    if (rightClick) {
        this->mouseButtonState.updateY(false); //Released rightclick
    } else {
        this->mouseButtonState.updateX(false); //Released leftclick
    }
    if (x == this->lastMouseDownPos.getX() && y == this->lastMouseDownPos.getY()) { //Only if we don't move mouse when clicking
        if (rightClick) {
            this->wasMouseButtonClicked.updateY(true);
        } else {
            this->wasMouseButtonClicked.updateX(true);
        }
    }

    if (this->wasMouseButtonClicked.getX() && y == 0) { //Check if we clicked on menu item
        unsigned int xOffset =
            this->windowDimensions.getMargin().getX() +
            this->windowDimensions.getBorderThickness().getX() +
            this->title.size() + 1;
        for (MenuItem* menuItem : this->menuItems) {
            if (x >= xOffset && x < xOffset + menuItem->getTitle().size()) {
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
        this->mouseButtonState.updateY(true); //Pressed rightclick
    } else {
        this->mouseButtonState.updateX(true); //Pressed leftclick
    }
    return false;
}

bool Window::onMouseMove(unsigned int x, unsigned int y) {
    this->currentMousePos.update(x,y);
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
        content = this->borderRenderer->encapsulateContent(content, this->title, this->menuItems, this->focus, this->windowDimensions, this->currentMousePos.getX(), this->currentMousePos.getY());
    }
    return content;
}

void Window::tick() {
    if (this->wasMouseButtonClicked.getX()) this->wasMouseButtonClicked.updateX(false);
    if (this->wasMouseButtonClicked.getY()) this->wasMouseButtonClicked.updateY(false);
}
