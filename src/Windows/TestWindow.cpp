//
// Created by et118 on 04/01/2026.
//

#include "../../include/Windows/TestWindow.h"
#include "../../include/BorderRenderers/SimpleBorderRenderer.h"
#include <iostream>
#include <ostream>


TestWindow::TestWindow() : Window(
    "TestWindow",
    {{1,1,1,1},{0,0,0,0},{0,0,0,0}},
    new SimpleBorderRenderer(),
    std::vector<MenuItem*>{
        new MenuItem("Menu1",[](std::string){std::cout<<"Menu1"<<std::endl;}),
        new MenuItem("Menu2",[](std::string){std::cout<<"Menu2"<<std::endl;}),
        new MenuItem("Menu3",[](std::string){std::cout<<"Menu3"<<std::endl;}),
    }
) {

}

Content TestWindow::renderContent() {
    Content content;
    content.addLine("01234567890");
    content.addLine("A Longer Test Line 2");
    content.addLine("");
    content.addLine("ENDLINE");
    return content;
}

void TestWindow::tick() {

}
