//
// Created by et118 on 12/17/25.
//
#include "../../include/Util/Content.h"

#include <iostream>
#include <ostream>

size_t Content::widthOfLine(const std::string& line) {
    size_t width = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '\x1B' && i + 1 < line.size() && line[i + 1] == '[') { //If its an ansi escape code. skip over it.
            i += 2;
            while (i < line.size() && line[i] != 'm') i++;
            continue;
        }

        unsigned char c = line[i];
        if (c < 128) { //Normal characters (1byte, 1 width)
            width += 1;
        } else if ((c & 0xE0) == 0xC0) { //UTF-8 (2byte, 1 width)
            width += 1;
            i++;
        } else if ((c & 0xF0) == 0xE0) { //Special (3byte, 2 width)
            if (i + 2 < line.size()) {
                unsigned char b1 = line[i];
                unsigned char b2 = line[i + 1];
                unsigned char b3 = line[i + 2];

                // ├ and ─ and └ needs custom width
                if (b1 == 0xE2 && b2 == 0x94 && (b3 == 0x9C || b3 == 0x80 || b3 == 0x94)) {
                    width += 1;
                } else {
                    width += 2;
                }
            }
            /*width += 2;*/
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
        if (line[i] == '\x1B' && i + 1 < line.size() && line[i + 1] == '[') {
            i += 2;
            while (i < line.size() && line[i] != 'm') i++;
            continue;
        }

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
/*Example of how it works with ansi escape codes for getCharacter()
 * "Hey \x1B[1mthis is bold\x1B[22m and \x1B[3mthis is italics\x1B[23m"
 * 0-3: "Hey "
 * 4: "\x1B[1mt"
 * 5-15: "his is bold"
 * 16: "\x1B[22m "
 * 17-20: "and "
 * 21: "\x1B[3mt"
 * 22-34: "his is italic"
 * 35: "s\x1B[23m"
 *
 * Aka. if the index is on an ansi code, before the end, it groups together the ansi code with the character
 */
std::string Content::getCharacter(std::string line, size_t index) {
    size_t characterCounter = 0;
    size_t totalCharacters = getNumCharacters(line);
    std::string pendingAnsi;

    for (size_t i = 0; i < line.size(); i++) {
        const unsigned char c = line[i];
        std::string character;

        if (c == '\x1B' && i + 1 < line.size() && line[i + 1] == '[') {
            size_t start = i;
            i += 2;
            while (i < line.size() && line[i] != 'm') i++;
            pendingAnsi += line.substr(start, i - start + 1);
            continue;
        }

        if (c < 128) { //Normal characters (1byte, 1 width)
            character = line.substr(i, 1);
        } else if ((c & 0xE0) == 0xC0) { //UTF-8 (2byte, 1 width)
            character = line.substr(i, 2);
            i++;
        } else if ((c & 0xF0) == 0xE0) { //Special (3byte, 2 width)
            character = line.substr(i, 3);
            i += 2;
        } else if ((c & 0xF8) == 0xF0) { //Emojis (4byte, 2 width)
            character = line.substr(i, 4);
            i += 3;
        }

        if (characterCounter == index) {
            std::string result = pendingAnsi + character;
            if (characterCounter == totalCharacters + 1) {
                size_t j = i + 1;
                while (j < line.size()) {
                    if (line[j] == '\x1B' && j + 1 < line.size() && line[j + 1] == '[') {
                        size_t start = j;
                        j += 2;
                        while (j < line.size() && line[j] != 'm') j++;
                        result += line.substr(start, j - start + 1);
                    }
                    j++;
                }
            }
            return result;
        }

        characterCounter++;
        pendingAnsi.clear();
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
        this->lineWidths[index] = widthOfLine(newLine);
    }
}

size_t Content::getLineWidth(size_t index) const {
    if (index >= lines.size()) return 0;
    return this->lineWidths.at(index);
}

std::string Content::getLine(size_t index) const {
    if (this->lines.empty() || index >= lines.size()) return "";
    return this->lines.at(index);
}

size_t Content::getNumLines() const {
    return this->lines.size();
}


