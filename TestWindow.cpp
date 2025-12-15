//
// Created by et118 on 12/7/25.
//

#include "EdgeDimensions.h"
#include "LineBorderRenderer.h"
#include "TestWindow.h"
#include <iostream>

TestWindow::TestWindow() : Window(
        "TestWindow",
        new LineBorderRenderer(),
        {0,0,0,0},
        {0,0,0,0},
        {1,1,1,1},
        0,
        0,
        0,
        0){
}

void TestWindow::tick() {
}


Content TestWindow::renderContent() {
    Content content;
    content.addLine("01234567890");
    content.addLine("A Longer Test Line 2");
    content.addLine("");
    content.addLine("ENDLINE");
    return content;
}
