//
// Created by et118 on 04/01/2026.
//

#ifndef CPP_EDITOR_TESTWINDOW_H
#define CPP_EDITOR_TESTWINDOW_H
#include "Window.h"
#include "../BorderRenderers/MenuItem.h"
class TestWindow final : public Window {
private:
public:
    TestWindow();

    static void exampleCallback(Window* window, std::string title);
    void tick() override;
    Content renderContent() override;
};
#endif //CPP_EDITOR_TESTWINDOW_H