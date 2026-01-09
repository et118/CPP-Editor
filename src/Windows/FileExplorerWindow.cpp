//
// Created by et118 on 09/01/2026.
//
#include "../../include/Windows/FileExplorerWindow.h"
#include "../../include/BorderRenderers/SimpleBorderRenderer.h"
#include <iostream>

FileExplorerWindow::FileExplorerWindow(const std::string& path)
    : Window(
        "Explorer",
        {{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        new SimpleBorderRenderer(),
        std::vector<MenuItem*>{}), currentPath(path) {
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
    content.addLine("..");
    for (const std::filesystem::directory_entry& item : std::filesystem::directory_iterator(currentPath)) {
        if (item.is_directory()) {
            std::cout << item.path().filename().string() << std::endl;
            content.addLine("🗀" + item.path().filename().string());
            std::cout << content.getLine(content.getNumLines()-1) << std::endl;
        } else {
            content.addLine(item.path().filename().string());
        }
    }
    return content;
}

void FileExplorerWindow::tick() {
    unsigned int mouseX = this->currentMousePos.getX();
    unsigned int mouseY = this->currentMousePos.getY();
    unsigned int contentHeight = this->windowDimensions.getContentAreaSize().getY();
    if (this->wasMouseButtonClicked.getX() && mouseX > 0 && mouseX <= this->windowDimensions.getContentAreaSize().getX()) {
        if (mouseY == 1) { // the .. option
            this->updateCurrentPath(this->currentPath.parent_path());
        } else {
            for (int i = 0; i < this->items.size(); i++) {
                std::filesystem::directory_entry item = this->items[i];
                if (i + 1 < contentHeight) {
                    if (item.is_directory()) {
                        this->updateCurrentPath(item.path());
                    } else {
                        /*TODO open file in editor. Add editor pointer reference to constructor*/
                    }
                }
            }
        }

    }
    Window::tick();
}