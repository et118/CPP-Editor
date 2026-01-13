//
// Created by et118 on 12/01/2026.
//

#ifndef CPP_EDITOR_TERMINALWINDOW_H
#define CPP_EDITOR_TERMINALWINDOW_H
#include "Window.h"
#include "EditorWindow.h"
class TerminalWindow : public Window {
private:
    EditorWindow* editorWindow;
    Content terminalOutput;

    std::filesystem::path editorOpenFile;
    bool hasRunnableFileOpen;

    bool isRunnableFile(const std::string& filename);
public:
    TerminalWindow(EditorWindow* editorWindow);

    Content runFile() const;
    void updateTerminalOutput(const Content& newContent);

    Content renderContent() override;
    void tick() override;
};
#endif //CPP_EDITOR_TERMINALWINDOW_H