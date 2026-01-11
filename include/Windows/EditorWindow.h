//
// Created by et118 on 10/01/2026.
//

#ifndef CPP_EDITOR_EDITORWINDOW_H
#define CPP_EDITOR_EDITORWINDOW_H
#include <filesystem>
#include "../Util/Content.h"
#include "Window.h"
class EditorWindow : public Window {
private:
    std::filesystem::path currentOpenFile;
    Content currentFileContents;
    Content currentRenderContents;

    bool wasFileChanged;
    bool isFileChanged;
    bool hasOpenFile;
    Vector2D<unsigned int> lastCursorPosition;
    Vector2D<unsigned int> cursorPosition;
    Vector2D<unsigned int> scroll;
    unsigned int savedCursorPositionX;

    void updateScroll();
    void updateTitle();

    void moveCursorUp();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight();
public:
    EditorWindow(const std::string& path = "");

    void openFile(const std::filesystem::path& path);
    void closeFile();
    void saveFile();

    bool onKeyboardInput(KeyEvent& event) override;
    Content renderContent() override;
    void tick() override;
};
#endif //CPP_EDITOR_EDITORWINDOW_H