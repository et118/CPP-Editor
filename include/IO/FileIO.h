//
// Created by et118 on 13/01/2026.
//

#ifndef CPP_EDITOR_FILEIO_H
#define CPP_EDITOR_FILEIO_H

#include <filesystem>
#include "../Util/Content.h"

namespace FileIO {
    std::filesystem::directory_iterator getDirectoryListings(const std::filesystem::path& path);

    Content readFileAsContent(const std::filesystem::path& filePath);

    bool writeFileAsContent(const std::filesystem::path& filePath, const Content& content);

    bool ensureParentPath(const std::filesystem::path& path);
    bool doesFileExist(const std::filesystem::path& filePath);

}
#endif //CPP_EDITOR_FILEIO_H