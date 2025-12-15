//
// Created by et118 on 12/7/25.
//

#ifndef SKETCH3_TESTWINDOW_H
#define SKETCH3_TESTWINDOW_H
#include "Window.h"
class TestWindow final : public Window {

public:
    TestWindow();
    void tick() override;
    Content renderContent() override;

};
#endif //SKETCH3_TESTWINDOW_H