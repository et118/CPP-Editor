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
#include "../IO/KeyEvent.h"

class Window {
private:
    BorderRenderer* borderRenderer;
    std::vector<MenuItem*> menuItems;
protected:
    Window(const std::string& title, const WindowDimensions& windowDimensions, BorderRenderer* borderRenderer, const std::vector<MenuItem*>& menuItems);
    Vector2D<unsigned int> currentMousePos;
    Vector2D<unsigned int> lastMousePos;
    Vector2D<unsigned int> lastMouseDownPos;
    Vector2D<bool> mouseButtonState; /*x: left, y: right*/
    Vector2D<bool> wasMouseButtonClicked; /*x: left, y: right*/
    bool alive; /*false if window should close next tick*/
    bool focus; /*is mouse actively hovering over window*/
    std::string title;
public:
    WindowDimensions windowDimensions;
    bool isAlive() const;
    void setAlive(bool alive);
    void setFocused(bool focused);

    virtual ~Window();
    virtual void tick(); //Make sure to call at end when overridden
    virtual Content renderContent() = 0;

    /*return value bool is if callback is consumed*/
    virtual bool onMouseDown(unsigned int x, unsigned int y, bool rightClick); //Call at beginning when overridden
    virtual bool onMouseMove(unsigned int x, unsigned int y); //Call at beginning when overridden
    virtual bool onMouseUp(unsigned int x, unsigned int y, bool rightClick); //Call at beginning when overridden
    virtual bool onKeyboardInput(KeyEvent& event); //Call at beginning when overridden
    Content render();
};
#endif //CPP_EDITOR_WINDOW_H