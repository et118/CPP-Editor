#include <iostream>
#include <thread>
#include "include/Util/Content.h"
#include "include/IO/TerminalIO.h"
#include "include/Windows/RecursiveWindow.h"
#include "include/Windows/FileExplorerWindow.h"
#include "include/Windows/EditorWindow.h"
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

static RecursiveWindow mainWindow{}; //Yes, this is our only public static variable, just so it can be accessed from the callback below
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

    termios original = TerminalIO::takeControlOfTerminal();
    TerminalIO::bindResizeCallback(onResize);

    struct winsize w = TerminalIO::getWindowSize();
    onResize(w.ws_col, w.ws_row); //Call one time manually on program start to get initial window size
    TerminalIO::clearTerminal();

    //Safetynet for exceptions that i might have forgotten to handle
    try {
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
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); //Arbitrary sleep value
        }
    } catch (const std::exception& e) {
        std::cout << "Exception Caught. Trying to autosave" << std::endl;
        try {
            editorWindow.saveFile();
            std::cout << "Saved open file successfully!" << std::endl;
        } catch (const std::exception& e2) {
            std::cout << "Failed to autosave file" << std::endl;
        }
    }
    TerminalIO::releaseControlOfTerminal(original);
    return 0;
}