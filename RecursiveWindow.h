//
// Created by et118 on 12/4/25.
//

#ifndef SKETCH3_RECURSIVEWINDOW_H
#define SKETCH3_RECURSIVEWINDOW_H
#include "Window.h"
#include "Content.h"
#include <vector>

class RecursiveWindow : public Window {
protected:
    std::vector<Window*> innerWindows;
    bool horizontal;
public:
    RecursiveWindow();
    void addWindow(Window* window);
    Content renderContent() override;
    void tick() override;
};
#endif //SKETCH3_RECURSIVEWINDOW_H