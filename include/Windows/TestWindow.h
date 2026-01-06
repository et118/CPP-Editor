//
// Created by et118 on 04/01/2026.
//

#ifndef CPP_EDITOR_TESTWINDOW_H
#define CPP_EDITOR_TESTWINDOW_H
#include "Window.h"
class TestWindow final : public Window {

public:
    TestWindow();
    void tick() override;
    Content renderContent() override;
};
#endif //CPP_EDITOR_TESTWINDOW_H