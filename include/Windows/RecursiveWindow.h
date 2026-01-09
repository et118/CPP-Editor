//
// Created by et118 on 04/01/2026.
//

#ifndef CPP_EDITOR_RECURSIVEWINDOW_H
#define CPP_EDITOR_RECURSIVEWINDOW_H
#include <vector>
#include "Window.h"
class RecursiveWindow : public Window {
private:
    std::vector<Window*> innerWindows;
    Window* lastFocusedWindow;
    unsigned int extraPadding;
    int isInsideInnerWindow(unsigned int x, unsigned int y, unsigned int* relativeX, unsigned int* relativeY) const; //-1 if no window, otherwise window index
public:
    RecursiveWindow();
    bool horizontal;
    void addWindow(Window* window);
    Content renderContent() override;
    void tick() override;
    bool onMouseDown(unsigned int x, unsigned int y, bool rightClick) override;
    bool onMouseMove(unsigned int x, unsigned int y) override;
    bool onMouseUp(unsigned int x, unsigned int y, bool rightClick) override;
    bool onKeyboardInput(char key) override;
};
#endif //CPP_EDITOR_RECURSIVEWINDOW_H