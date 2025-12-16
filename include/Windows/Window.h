//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_WINDOW_H
#define CPP_EDITOR_WINDOW_H
#include <string>
#include <vector>
#include "WindowDimensions.h"
class Window {
private:
    WindowDimensions windowDimensions;
    BorderRenderer* borderRenderer;
    std::vector<MenuItem*> menuItems;
protected:
    Window(std::string& title, WindowDimensions& windowDimensions, BorderRenderer* borderRenderer, std::vector<MenuItem*>& menuItems);
    bool alive; /*false if window should close next tick*/
    bool hovered; /*is mouse actively hovering over window*/
    std::string title;
public:
    bool isAlive();
    void setHovered(bool hover);

    virtual ~Window();
    virtual void tick() = 0;
    virtual Content renderContent() = 0;

    /*return value is if callback is consumed*/
    bool onMouseClick(unsigned int x, unsigned int y, bool rightClick); //Default implementation for MenuItems
    bool onKeyboardInput(char key); //Default implementation for keyboard shortcuts
    Content render();
};
#endif //CPP_EDITOR_WINDOW_H