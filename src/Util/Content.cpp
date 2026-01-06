//
// Created by et118 on 12/17/25.
//
#include "../../include/Util/Content.h"

void Content::addLine(const std::string &line) {
    this->lines.emplace_back(line);

}

void Content::removeLine(size_t index) {
    this->lines.erase(this->lines.begin() + index);
}

void Content::changeLine(size_t index, const std::string& newLine) {
    if (index >= lines.size()) {
        for (size_t i = lines.size(); i < index; i++) {
            this->addLine("");
        }
        this->addLine(newLine);
    } else {
        this->lines[index] = newLine;
    }
}

std::string Content::getLine(size_t index) {
    if (this->lines.empty() || index >= lines.size()) return "";
    return this->lines.at(index);
}

size_t Content::getNumLines() const {
    return this->lines.size();
}


