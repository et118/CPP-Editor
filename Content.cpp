//
// Created by et118 on 12/2/25.
//

#include "Content.h"
#include <iostream>

size_t Content::getNumLines() const {
    return this->lines.size();
}

void Content::addLine(const std::string &line) {
    this->lines.emplace_back(line);
}

std::string Content::getLine(const size_t index) {
    if (this->lines.empty() || index >= lines.size()) return "";
    return this->lines.at(index);
}

Content& Content::operator+=(Content &other) {
    for (size_t i = 0; i < other.getNumLines(); i++) {
        if (this->getNumLines() == i) this->lines.emplace_back("");
        this->lines[i] += other.getLine(i);
    }
    return *this;
}
