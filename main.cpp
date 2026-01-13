#include "include/BorderRenderers/SimpleBorderRenderer.h"
#include <iostream>
#include <thread>
#include <sys/ioctl.h>

#include "include/IO/TerminalIO.h"
#include "include/Windows/RecursiveWindow.h"
#include "include/Windows/FileExplorerWindow.h"
#include "include/Windows/EditorWindow.h"
#include "include/Util/Content.h"
#include "include/Util/StringUtils.h"
#include "include/Windows/TerminalWindow.h"

std::filesystem::path resolvePath(const std::string& path) {
    if (path == ".") {
        return std::filesystem::current_path();
    }
    if (path == "~") {
        return std::filesystem::path{std::getenv("HOME")};
    }
    return std::filesystem::path{path};

}
static RecursiveWindow mainWindow{};
void onResize(unsigned int width, unsigned int height) {
    mainWindow.getWindowDimensions().setContentAreaSize({width,height - 1});
    TerminalIO::clearTerminal();
}

int main(int argc, char* argv[]) {
    std::filesystem::path currentPath;
    if (argc > 1) {
        currentPath = resolvePath(argv[1]);
    } else {
        currentPath = std::filesystem::current_path();
    }

    RecursiveWindow subWindow{};
    EditorWindow editorWindow{};
    FileExplorerWindow explorerWindow{currentPath, &editorWindow};
    TerminalWindow terminalWindow{&editorWindow};
    subWindow.setHorizontal(true);
    subWindow.addWindow(&explorerWindow);
    subWindow.addWindow(&editorWindow);
    subWindow.getWindowDimensions().setMinSize({0,0});
    explorerWindow.getWindowDimensions().setMaxSize({20,0});
    terminalWindow.getWindowDimensions().setMaxSize({0,10});

    mainWindow.setHorizontal(false);
    mainWindow.addWindow(&subWindow);
    mainWindow.addWindow(&terminalWindow);

    mainWindow.getWindowDimensions().setContentAreaSize({51,25});
    mainWindow.tick();

    termios original = TerminalIO::takeControlOfTerminal();

    TerminalIO::bindResizeCallback(onResize);

    struct winsize w = TerminalIO::getWindowSize();
    onResize(w.ws_col, w.ws_row); //Call manually on program start to get initial window size

    TerminalIO::clearTerminal();
    while (true) {
        int status = TerminalIO::handleWindowInput(&mainWindow);
        if (status == 1) {//Quit signal CTRL + Q
            break;
        }
        Content content = mainWindow.render();
        std::cout << "\x1B[H"; //Set cursor to beginning of window (this makes us overwrite last frame, making us not have to clear the entire terminal)
        for (size_t i = 0; i < content.getNumLines(); i++) {
            std::cout << content.getLine(i) << "\n";
        }
        mainWindow.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    TerminalIO::releaseControlOfTerminal(original);
    return 0;
}