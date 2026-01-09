//
// Created by et118 on 09/01/2026.
//

#ifndef CPP_EDITOR_FILEEXPLORERWINDOW_H
#define CPP_EDITOR_FILEEXPLORERWINDOW_H
#include <filesystem>
#include "Window.h"

class FileExplorerWindow : public Window {
private:
    std::filesystem::path currentPath;
    std::vector<std::filesystem::directory_entry> items;

    void updateCurrentPath(const std::filesystem::path& newPath);
public:
    FileExplorerWindow(const std::string& path);

    Content renderContent() override;
    void tick() override;
};
#endif //CPP_EDITOR_FILEEXPLORERWINDOW_H