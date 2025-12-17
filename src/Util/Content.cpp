//
// Created by et118 on 12/17/25.
//
#include "../../include/Util/Content.h"

void Content::addLine(const std::string &line) {
    this->lines.emplace_back(line);
}

std::string Content::getLine(size_t index) {
    if (this->lines.empty() || index >= lines.size()) return "";
    return this->lines.at(index);
}

size_t Content::getNumLines() const {
    return this->lines.size();
}


