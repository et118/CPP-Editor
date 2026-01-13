//
// Created by et118 on 13/01/2026.
//
#include "../../include/IO/FileIO.h"
#include <fstream>

std::filesystem::directory_iterator FileIO::getDirectoryListings(const std::filesystem::path &path) {
    if (std::filesystem::is_regular_file(path)) { //If its a file, get directory listings inside parent dir
        return std::filesystem::directory_iterator(path.parent_path());
    }
    return std::filesystem::directory_iterator(path);
}

Content FileIO::readFileAsContent(const std::filesystem::path& filePath) {
    Content content;
    std::ifstream file;
    file.open(filePath);
    if (!file.is_open() || std::filesystem::is_directory(filePath)) {
        content.addLine("Error");
        content.addLine("Could not open file");
        file.close();
        return content;
    }

    for (std::string line; std::getline(file, line);) { //Thanks https://stackoverflow.com/questions/66927431/why-my-getline-does-not-read-empty-lines-of-a-file
        if (!line.empty() && line.back() == '\r') line.resize(line.size() - 1);
        content.addLine(line);
    }
    file.close();
    return content;
}

bool FileIO::ensureParentPath(const std::filesystem::path &path) {
    if (path.has_parent_path()) {  //incase path has a parent folder, we ensure its created
        std::error_code ec;
        std::filesystem::create_directories(path.parent_path(), ec);
        return !ec;
    }
    return true;
}

bool FileIO::writeFileAsContent(const std::filesystem::path &filePath, const Content &content) {
    //Write file, write binary, overwrite file
    std::ofstream file{filePath, std::ios::out | std::ios::binary |std::ios::trunc};
    if (file) {
        for (size_t i = 0; i < content.getNumLines(); i++) {
            file << content.getLine(i) << '\n';
        }
        file.flush(); //Make sure its all written before we close
        file.close();
        return true;
    }
    file.close();
    return false;
}

bool FileIO::doesFileExist(const std::filesystem::path &filePath) {
    return std::filesystem::exists(filePath);
}
