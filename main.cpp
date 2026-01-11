#include "include/BorderRenderers/SimpleBorderRenderer.h"
#include <iostream>
#include <thread>

#include "include/IO/TerminalIO.h"
#include "include/Windows/TestWindow.h"
#include "include/Windows/RecursiveWindow.h"
#include "include/Windows/FileExplorerWindow.h"
#include "include/Windows/EditorWindow.h"
#include "include/Util/Content.h"
#include "include/Util/StringUtils.h"

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

    RecursiveWindow mainWindow{};
    TestWindow terminalWindow{};

    terminalWindow.windowDimensions.setMaxSize({0,5});

    RecursiveWindow subWindow{};
    EditorWindow editorWindow{};
    FileExplorerWindow explorerWindow{currentPath.string(), &editorWindow};
    subWindow.horizontal = true;
    subWindow.addWindow(&explorerWindow);
    subWindow.addWindow(&editorWindow);
    subWindow.windowDimensions.setMinSize({0,0});
    explorerWindow.windowDimensions.setMaxSize({20,0});

    mainWindow.horizontal = false;
    mainWindow.addWindow(&subWindow);
    mainWindow.addWindow(&terminalWindow);

    mainWindow.windowDimensions.setContentAreaSize({51,25});
    mainWindow.tick();

    termios original = TerminalIO::takeControlOfTerminal();

    time_t start = time(0);


    TerminalIO::clearTerminal();
    while (true) {

        if (time(0) - start > 100) {
            break;
        }
        TerminalIO::handleWindowInput(&mainWindow);
        Content content = mainWindow.render();
        std::cout << "\x1B[H";
        for (size_t i = 0; i < content.getNumLines(); i++) {
            std::cout << content.getLine(i) << "\n";
        }
        mainWindow.tick();
        //mainWindow.setAlive(true); //Make sure its always open
        //if (!editorWindow.isAlive() && !explorerWindow.isAlive() && !terminalWindow.isAlive()) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    TerminalIO::releaseControlOfTerminal(original);
    //mainWindow.onMouseUp(27,0,false);
    return 0;
}