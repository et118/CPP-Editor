#include "include/BorderRenderers/SimpleBorderRenderer.h"
#include <iostream>
int main() {
    SimpleBorderRenderer borderRenderer;
    Content inputContent;
    inputContent.addLine("Testing stuff");
    inputContent.addLine("Testing some more stuff");

    std::string title = "Title";
    std::vector<MenuItem*> menuItems;
    menuItems.push_back(new MenuItem("Menu1", [](std::string){}));
    menuItems.push_back(new MenuItem("Menu2", [](std::string){}));
    menuItems.push_back(new MenuItem("Menu3", [](std::string){}));

    WindowDimensions windowDimensions{
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {30,10}};

    Content outputContent = borderRenderer.encapsulateContent(
        inputContent,
        title,menuItems,
        false,windowDimensions,
        0, 0);

    for (size_t i = 0; i < outputContent.getNumLines(); i++) {
        std::cout << outputContent.getLine(i) << "\n";
    }
    return 0;
}
