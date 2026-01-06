#include "include/BorderRenderers/SimpleBorderRenderer.h"
#include <iostream>

#include "include/Windows/TestWindow.h"
#include "include/Windows/RecursiveWindow.h"

int main() {
    TestWindow testWindow{};
    TestWindow testWindow2{};
    //testWindow.windowDimensions.setMaxSize({0,0});
    //testWindow2.windowDimensions.setMaxSize({0,0});
    //testWindow2.windowDimensions.setMinSize({2,7}); //TODO we need to make sure the minimums are set first

    RecursiveWindow recursiveWindow{};
    recursiveWindow.windowDimensions.setContentAreaSize({20,10}); //Normally maybe not have this, but main one must
    recursiveWindow.horizontal = false;

    recursiveWindow.addWindow(&testWindow);
    recursiveWindow.addWindow(&testWindow2);

    testWindow.windowDimensions.setMaxSize({0,4});
    testWindow2.windowDimensions.setMinSize({0,5});

    recursiveWindow.tick();
    Content content = recursiveWindow.render();

    for (size_t i = 0; i < content.getNumLines(); i++) {
        std::cout << content.getLine(i) << "\n";
    }

    return 0;
}
