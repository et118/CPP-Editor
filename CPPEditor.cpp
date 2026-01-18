//
// Created by et118 on 18/01/2026.
//
#include <filesystem>
#include <iostream>
#include <thread>
#include "CPPEditor.h"
#include "include/Windows/EditorWindow.h"
#include "include/Windows/FileExplorerWindow.h"
#include "include/Windows/TerminalWindow.h"
#include "include/IO/TerminalIO.h"
#include "include/IO/FileIO.h"

CPPEditor::CPPEditor(int argc, char* argv[]) {
    if (argc > 1) {
        this->startPath = FileIO::resolvePath(argv[1]);
    } else {
        this->startPath = FileIO::getCurrentPath();
    }
}

RecursiveWindow CPPEditor::mainWindow = RecursiveWindow{}; //Definition of static mainWindow

int CPPEditor::run() {
    RecursiveWindow subWindow{};
    EditorWindow editorWindow{};
    FileExplorerWindow explorerWindow{startPath, &editorWindow};
    TerminalWindow terminalWindow{&editorWindow};

    subWindow.setHorizontal(true);
    subWindow.addWindow(&explorerWindow);
    subWindow.addWindow(&editorWindow);

    subWindow.getWindowDimensions().setMinSize({0, 0});
    explorerWindow.getWindowDimensions().setMaxSize({20, 0});
    terminalWindow.getWindowDimensions().setMaxSize({0, 10});

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
            std::this_thread::sleep_for(std::chrono::milliseconds(15)); //Arbitrary sleep value
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

void onResize(unsigned int width, unsigned int height) {
    CPPEditor::mainWindow.getWindowDimensions().setContentAreaSize({width,height - 1}); //-1 because of WSL in windows
    TerminalIO::clearTerminal();
}
