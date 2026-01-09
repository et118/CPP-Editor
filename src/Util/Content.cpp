//
// Created by et118 on 12/17/25.
//
#include "../../include/Util/Content.h"

#include <iostream>
#include <ostream>

size_t Content::widthOfLine(const std::string& line) {
    size_t width = 0;
    for (size_t i = 0; i < line.size(); i++) {
        unsigned char c = line[i];
        if (c < 128) { //Normal characters (1byte, 1 width)
            width += 1;
        } else if ((c & 0xE0) == 0xC0) { //UTF-8 (2byte, 1 width)
            width += 1;
            i++;
        } else if ((c & 0xF0) == 0xE0) { //Special (3byte, 2 width)
            width += 2;
            i += 2;
        } else if ((c & 0xF8) == 0xF0) { //Emojis (4byte, 2 width)
            width += 2;
            i += 3;
        }
    }
    return width;
}

size_t Content::getNumCharacters(const std::string &line) {
    size_t characterCounter = 0;
    for (size_t i = 0; i < line.size(); i++) {
        const unsigned char c = line[i];

        if (c < 128) { //Normal characters (1byte, 1 width)
            characterCounter++;
        } else if ((c & 0xE0) == 0xC0) { //UTF-8 (2byte, 1 width)
            i++;
            characterCounter++;
        } else if ((c & 0xF0) == 0xE0) { //Special (3byte, 2 width)
            i += 2;
            characterCounter++;
        } else if ((c & 0xF8) == 0xF0) { //Emojis (4byte, 2 width)
            i += 3;
            characterCounter++;
        }
    }
    return characterCounter;
}

std::string Content::getCharacter(std::string line, size_t index) {
    size_t characterCounter = 0;
    for (size_t i = 0; i < line.size(); i++) {
        const unsigned char c = line[i];
        std::string character;

        if (c < 128) { //Normal characters (1byte, 1 width)
            character = line.substr(i, 1);
            characterCounter++;
        } else if ((c & 0xE0) == 0xC0) { //UTF-8 (2byte, 1 width)
            character = line.substr(i, 2);
            i++;
            characterCounter++;
        } else if ((c & 0xF0) == 0xE0) { //Special (3byte, 2 width)
            character = line.substr(i, 3);
            i += 2;
            characterCounter++;
        } else if ((c & 0xF8) == 0xF0) { //Emojis (4byte, 2 width)
            character = line.substr(i, 4);
            i += 3;
            characterCounter++;
        }

        if (characterCounter - 1 == index) return character;
    }
    return "";
}

void Content::addLine(const std::string &line) {
    this->lines.emplace_back(line);
    this->lineWidths.emplace_back(this->widthOfLine(line));
}

void Content::removeLine(size_t index) {
    this->lines.erase(this->lines.begin() + index);
    this->lineWidths.erase(this->lineWidths.begin() + index);
}

void Content::changeLine(size_t index, const std::string& newLine) {
    if (index >= lines.size()) {
        for (size_t i = lines.size(); i < index; i++) {
            this->addLine("");
        }
        this->addLine(newLine);
    } else {
        this->lines[index] = newLine;
        this->lineWidths[index] = this->widthOfLine(newLine);
    }
}

size_t Content::getLineWidth(size_t index) const {
    if (index >= lines.size()) return 0;
    return this->lineWidths.at(index);
}

std::string Content::getLine(size_t index) {
    if (this->lines.empty() || index >= lines.size()) return "";
    return this->lines.at(index);
}

size_t Content::getNumLines() const {
    return this->lines.size();
}


