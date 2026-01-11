//
// Created by et118 on 09/01/2026.
//
#include "../../include/Windows/FileExplorerWindow.h"
#include "../../include/BorderRenderers/SimpleBorderRenderer.h"
#include <iostream>

#include "../../include/Util/StringUtils.h"
//TODO scrolling functionality
FileExplorerWindow::FileExplorerWindow(const std::string& path, EditorWindow* editorWindow)
    : Window(
        "Explorer",
        {{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        new SimpleBorderRenderer(),
        std::vector<MenuItem*>{}), currentPath(path), editorWindow(editorWindow) {
    this->updateCurrentPath(path);
}

void FileExplorerWindow::updateCurrentPath(const std::filesystem::path& newPath) {

    this->currentPath = newPath;
    items.clear();
    for (const std::filesystem::directory_entry& item : std::filesystem::directory_iterator(currentPath)) {
        items.emplace_back(item);
    }
}

Content FileExplorerWindow::renderContent() {
    Content content;
    int index = 0;
    std::string doubleDotItem = this->currentPath.filename().string() + "/";
    content.addLine(this->currentMousePos.getY() == 1 ? StringUtils::to_bold(doubleDotItem) : doubleDotItem);
    for (const std::filesystem::directory_entry& item : this->items) {
        std::string line = "├─";
        if (index == this->items.size() - 1) line = "└─";
        line += item.path().filename().string();
        if (item.is_directory()) {
            line += "/";
        }
        if (this->currentMousePos.getY() == index + 2) line = StringUtils::to_bold(line);
        content.addLine(line);
        index++;
    }
    return content;
}

void FileExplorerWindow::tick() {
    unsigned int mouseX = this->currentMousePos.getX();
    unsigned int mouseY = this->currentMousePos.getY();
    unsigned int contentHeight = this->windowDimensions.getContentAreaSize().getY();
    if (this->wasMouseButtonClicked.getX() && mouseX > 0 && mouseX <= this->windowDimensions.getContentAreaSize().getX()
        && mouseY > 0 && mouseY <= contentHeight
    ) {
        if (mouseY == 1) { // the .. option
            this->updateCurrentPath(this->currentPath.parent_path());
        } else {
            for (int i = 0; i < this->items.size(); i++) {
                std::filesystem::directory_entry item = this->items[i];
                if (i == mouseY - 2) {
                    if (item.is_directory()) {
                        this->updateCurrentPath(item.path());
                    } else {
                        if (this->editorWindow) {this->editorWindow->openFile(item.path());}
                    }
                    break;
                }
            }
        }

    }
    Window::tick();
}