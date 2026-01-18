//
// Created by et118 on 12/01/2026.
//
#include "../../include/Windows/TerminalWindow.h"
#include "../../include/BorderRenderers/SimpleBorderRenderer.h"
#include "../../include/IO/FileIO.h"
TerminalWindow::TerminalWindow(EditorWindow *editorWindow) : Window(
    "Terminal",
    {{1,1,1,1},{0,0,0,0},{0,0,0,0}},
    new SimpleBorderRenderer(),
    std::vector<MenuItem*>{}), editorWindow(editorWindow), hasRunnableFileOpen(false) {
}

Content TerminalWindow::renderContent() {
    return this->terminalOutput;
}

bool TerminalWindow::isRunnableFile(const std::string &filename) { //TODO add more filetypes or change entire approach to implementing the terminal
    size_t position = filename.rfind('.');
    if (position == std::string::npos) return false; //if no dot in the filename
    std::string pythonExtension = filename.substr(position + 1);
    return pythonExtension == "py";
}

void TerminalWindow::updateTerminalOutput(const Content& newContent) {
    this->terminalOutput = newContent;
}

Content TerminalWindow::runFile() const {
    Content output;
    if (!FileIO::doesFileExist(this->editorOpenFile)) {
        output.addLine("The path " + this->editorOpenFile.string() + " is invalid");
        return output;
    }

    std::string command =
        "cd \"" + this->editorOpenFile.parent_path().string() + //cd into parent directory
        "\" && python3 \"" + this->editorOpenFile.filename().string() + "\""; //run python on filename

    //only linux
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        output.addLine("Failed to open pipe");
        return output;
    }
    //TODO we dont handle the error stream here yet.
    char buffer[4096]; //Must be real careful to avoid buffer overflows or out of bounds reads here
    while (fgets(buffer, sizeof(buffer), pipe)) {
        std::string line(buffer);

        if (!line.empty() && line.back() == '\n') line.pop_back(); //We got an extra newline at the end so we remove it
        output.addLine(line);
    }

    pclose(pipe);
    return output;
}

void TerminalWindow::tick() {
    this->editorOpenFile = this->editorWindow->getCurrentOpenFile();
    if (!hasRunnableFileOpen && this->isRunnableFile(editorOpenFile)) {
        hasRunnableFileOpen = true;
        this->addMenuItem(new MenuItem("Run", this, [](Window* window, std::string title) {
            TerminalWindow* w = dynamic_cast<TerminalWindow*>(window);
            w->updateTerminalOutput(w->runFile());
        }));
    } else if (hasRunnableFileOpen && !this->isRunnableFile(editorOpenFile)) {
        hasRunnableFileOpen = false;
        this->clearMenuItems();
        this->terminalOutput = Content();
    }
}