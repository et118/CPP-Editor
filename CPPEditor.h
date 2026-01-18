//
// Created by et118 on 18/01/2026.
//

#ifndef CPP_EDITOR_CPPEDITOR_H
#define CPP_EDITOR_CPPEDITOR_H
#include <filesystem>
#include "include/Windows/RecursiveWindow.h"

class CPPEditor {
private:
    std::filesystem::path startPath;
public:
    CPPEditor(int argc, char* argv[]);

    int run();

    static RecursiveWindow mainWindow; //Must be static for the callback function to access it.
};

void onResize(unsigned int width, unsigned int height); //Must be free for callbacks. There is probably a way to avoid this though with std::function
#endif //CPP_EDITOR_CPPEDITOR_H