//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_WINDOW_H
#define CPP_EDITOR_WINDOW_H
#include <string>
#include <vector>
#include "WindowDimensions.h"
#include "../Util/Vector2D.h"
#include "../Util/Content.h"
#include "../BorderRenderers/BorderRenderer.h"
#include "../BorderRenderers/MenuItem.h"
class Window {
private:
    BorderRenderer* borderRenderer;
    std::vector<MenuItem*> menuItems;
protected:
    Window(const std::string& title, const WindowDimensions& windowDimensions, BorderRenderer* borderRenderer, const std::vector<MenuItem*>& menuItems);
    Vector2D<unsigned int> mousePos;
    Vector2D<unsigned int> lastMouseDownPos;
    Vector2D<bool> mouseButtonDown; /*x: left, y: right*/
    bool alive; /*false if window should close next tick*/
    bool focus; /*is mouse actively hovering over window*/
    std::string title;
public:
    WindowDimensions windowDimensions;
    bool isAlive();
    void setHovered(bool hover);

    virtual ~Window();
    virtual void tick() = 0;
    virtual Content renderContent() = 0;

    /*return value bool is if callback is consumed*/
    virtual bool onMouseDown(unsigned int x, unsigned int y, bool rightClick);
    virtual bool onMouseMove(unsigned int x, unsigned int y);
    virtual bool onMouseUp(unsigned int x, unsigned int y, bool rightClick); //Default implementation for MenuItems
    virtual bool onKeyboardInput(char key); //Default implementation for keyboard shortcuts
    Content render();
};
#endif //CPP_EDITOR_WINDOW_H