//
// Created by et118 on 04/01/2026.
//
#include "../../include/BorderRenderers/SimpleBorderRenderer.h"

#include <codecvt>
#include <iostream>
#include <locale>

void SimpleBorderRenderer::addSpaces(size_t margin, std::string& line) const {
    for (size_t i = 0; i < margin; i++) {
        line += this->emptyChar;
    }
}

Content SimpleBorderRenderer::encapsulateContent(Content &content, std::string &title, std::vector<MenuItem *> &menuItems, bool hovered, WindowDimensions &dimensions, unsigned int mouseX, unsigned int mouseY) {
    Content newContent;/*TODO Make it so that if borderSize is 0, the border doesnt get drawn*/
    /*Upper Horizontal Line*/
    std::string line;

    std::wstring menuString;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> wide_converter;
    for (MenuItem* menuItem : menuItems) {
        menuString += wide_converter.from_bytes(menuItem->getTitle() + this->horizontalChar);
    }

    this->addSpaces(dimensions.getMargin().getX(), line);
    line += this->upperLeftCornerChar;

    for (size_t i = 0; i < dimensions.getPadding().getX() + dimensions.getContentAreaSize().getX() + dimensions.getPadding().getZ(); i++) {
        if (i < title.size()) {
            line += title[i];
        } else if (i > title.size() && i < title.size() + menuString.size()) {
            line += wide_converter.to_bytes(menuString[i - title.size() - 1]);
        } else {
            line += this->horizontalChar;
        }
    }
    line += this->upperRightCornerChar;
    this->addSpaces(dimensions.getMargin().getZ(), line);
    newContent.addLine(line);

    /*Middle Content*/

    for (size_t i = 0; i < dimensions.getPadding().getY(); i++) {
        line = "";
        this->addSpaces(dimensions.getMargin().getX(), line);
        line += this->verticalChar;
        this->addSpaces(dimensions.getPadding().getX() + dimensions.getContentAreaSize().getX() + dimensions.getPadding().getZ(), line);
        line += this->verticalChar;
        this->addSpaces(dimensions.getMargin().getZ(), line);
        newContent.addLine(line);
    }
    for (size_t i = 0; i < dimensions.getContentAreaSize().getY(); i++) {
        line = "";
        this->addSpaces(dimensions.getMargin().getX(), line);
        line += this->verticalChar;
        this->addSpaces(dimensions.getPadding().getX(), line);
        for (size_t k = 0; k < dimensions.getContentAreaSize().getX(); k++) {
            std::string contentLine = content.getLine(i);
            if (k > Content::widthOfLine(contentLine) - 1 || Content::widthOfLine(contentLine) == 0) {
                line += this->emptyChar;
            } else {
                std::string character = Content::getCharacter(contentLine, k);
                size_t width = Content::widthOfLine(character);
                if (k + 1 < dimensions.getContentAreaSize().getX()) { //Do we have space for 2 width character?
                    line += character;
                    k += width - 1;
                } else {
                    if (Content::widthOfLine(character) >= 2) {
                        line += this->emptyChar;
                    } else {
                        line += character;
                    }
                }
            }
        }
        this->addSpaces(dimensions.getPadding().getZ(), line);
        line += this->verticalChar;
        this->addSpaces(dimensions.getMargin().getZ(), line);
        newContent.addLine(line);
    }

    /*Lower Horizontal Line*/
    line = "";
    this->addSpaces(dimensions.getMargin().getX(), line);
    line += this->lowerLeftCornerChar;

    for (size_t i = 0; i < dimensions.getPadding().getX() + dimensions.getContentAreaSize().getX() + dimensions.getPadding().getZ(); i++) {
        line += this->horizontalChar;
    }
    line += this->lowerRightCornerChar;
    this->addSpaces(dimensions.getMargin().getZ(), line);
    newContent.addLine(line);

    return newContent;
}
