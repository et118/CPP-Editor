//
// Created by et118 on 04/01/2026.
//
#include "../../include/BorderRenderers/SimpleBorderRenderer.h"

#include <iostream>
#include <locale>

#include "../../include/Util/StringUtils.h"

void SimpleBorderRenderer::addSpaces(size_t margin, std::string& line) const {
    for (size_t i = 0; i < margin; i++) {
        line += this->emptyChar;
    }
}

Content SimpleBorderRenderer::encapsulateContent(Content &content, std::string &title, std::vector<MenuItem *> &menuItems, bool hovered, WindowDimensions &dimensions, unsigned int mouseX, unsigned int mouseY) {
    Content newContent;/*TODO Make it so that if borderSize is 0, the border doesnt get drawn*/
    /*Upper Horizontal Line*/
    std::string line;

    std::string menuString;
    for (MenuItem* menuItem : menuItems) {
        menuString += menuItem->getTitle() + this->horizontalChar;
    }

    this->addSpaces(dimensions.getMargin().getX(), line);
    line += this->upperLeftCornerChar;

    for (size_t i = 0; i < dimensions.getPadding().getX() + dimensions.getContentAreaSize().getX() + dimensions.getPadding().getZ(); i++) {
        size_t titleLength = Content::getNumCharacters(title);
        if (i < titleLength) {
            line += Content::getCharacter(title, i);
            //Insurance (though a bit redundant) if we dont have room to get the last title char with the ansi cancel codes
            if (i == dimensions.getPadding().getX() + dimensions.getContentAreaSize().getX() + dimensions.getPadding().getZ() - 1) {
                line += StringUtils::get_all_ansi_terminators();
            }
        } else if (i > titleLength && i < titleLength + Content::getNumCharacters(menuString) + 1) {
            line += Content::getCharacter(menuString, i - titleLength - 1);
            //Insurance again
            if (i == dimensions.getPadding().getX() + dimensions.getContentAreaSize().getX() + dimensions.getPadding().getZ() - 1) {
                line += StringUtils::get_all_ansi_terminators();
            }
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

        size_t iterationSafety = 0;
        size_t iterationSafetyMax = 10000;
        for (size_t k = 0; k < dimensions.getContentAreaSize().getX(); k++) {
            std::string contentLine = content.getLine(i);
            if (k > Content::widthOfLine(contentLine) - 1 || Content::widthOfLine(contentLine) == 0) {
                line += this->emptyChar;
            } else {
                std::string character = Content::getCharacter(contentLine, k);
                size_t width = Content::widthOfLine(character);
                if (width > 1 && k + (width - 1) < dimensions.getContentAreaSize().getX()) { //Do we have space for wider characters?
                    line += character;
                    k += width - 1;
                } else {
                    if (width >= 2) {
                        this->addSpaces(width - 1, line);
                        k += width - 1;
                    } else {
                        line += character;
                    }
                }
            }
            iterationSafety++; //TODO temporary check for infinite loops due to my linux install's compatibility issues with wsl.
            if (iterationSafety > iterationSafetyMax) break;
        }
        line += StringUtils::get_all_ansi_terminators();
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
