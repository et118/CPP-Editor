#include "include/BorderRenderers/SimpleBorderRenderer.h"
#include <iostream>

#include "include/Windows/TestWindow.h"
#include "include/Windows/RecursiveWindow.h"
#include "include/Windows/FileExplorerWindow.h"
#include "include/Util/Content.h"

std::filesystem::path resolvePath(const std::string& path) {
    if (path == ".") {
        return std::filesystem::current_path();
    } else if (path == "~") {
        return std::filesystem::path(std::getenv("HOME"));
    } else {
        return std::filesystem::path(path);
    }
}

int main(int argc, char* argv[]) {
    std::filesystem::path currentPath;
    if (argc > 1) {
        currentPath = resolvePath(argv[1]);
    } else {
        currentPath = std::filesystem::current_path();
    }

    TestWindow testWindow{};
    TestWindow testWindow2{};
    //testWindow.windowDimensions.setMaxSize({0,0});
    //testWindow2.windowDimensions.setMaxSize({0,0});
    //testWindow2.windowDimensions.setMinSize({2,7}); //TODO we need to make sure the minimums are set first

    /*RecursiveWindow recursiveWindow{};
    recursiveWindow.windowDimensions.setContentAreaSize({20,10}); //Normally maybe not have this, but main one must
    recursiveWindow.horizontal = true;

    recursiveWindow.addWindow(&testWindow);
    recursiveWindow.addWindow(&testWindow2);

    testWindow.windowDimensions.setMaxSize({4,0});
    testWindow2.windowDimensions.setMinSize({11,0});*/

    RecursiveWindow mainWindow{};
    TestWindow terminalWindow{};

    RecursiveWindow subWindow{};
    FileExplorerWindow explorerWindow{currentPath.string()};
    TestWindow editorWindow{};
    subWindow.horizontal = true;
    subWindow.addWindow(&explorerWindow);
    subWindow.addWindow(&editorWindow);
    subWindow.windowDimensions.setMinSize({0,6});
    explorerWindow.windowDimensions.setMaxSize({9,0});

    mainWindow.horizontal = false;
    mainWindow.addWindow(&subWindow);
    mainWindow.addWindow(&terminalWindow);

    mainWindow.windowDimensions.setContentAreaSize({50,10});
    mainWindow.tick();
    Content content = mainWindow.render();

    for (size_t i = 0; i < content.getNumLines(); i++) {
        std::cout << content.getLine(i) << "\n";
    }

    mainWindow.onMouseUp(27,0,false);

    return 0;
}
