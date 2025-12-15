//
// Created by et118 on 12/3/25.
//
#include "LineBorderRenderer.h"
#include <iostream>

LineBorderRenderer::LineBorderRenderer(BorderType borderType) {
    this->type = borderType;
    switch (borderType) {
        case Square: {
            this->verticalChar = "│";
            this->horizontalChar = "─";
            this->upperLeftCornerChar = "┌";
            this->upperRightCornerChar = "┐";
            this->lowerLeftCornerChar = "└";
            this->lowerRightCornerChar = "┘";
            this->mergeRight = "├";
            this->mergeLeft = "┤";
            this->mergeTop = "┴";
            this->mergeBottom = "┬";
            break;
        } case Smooth: {
            this->verticalChar = "│";
            this->horizontalChar = "─";
            this->upperLeftCornerChar = "╭";
            this->upperRightCornerChar = "╮";
            this->lowerLeftCornerChar = "╰";
            this->lowerRightCornerChar = "╯";
            break;
        } case Solid: {
            this->verticalChar = "██";
            this->horizontalChar = "██";
            this->upperLeftCornerChar = "██";
            this->upperRightCornerChar = "██";
            this->lowerLeftCornerChar = "██";
            this->lowerRightCornerChar = "██";
            break;
        }
    }
}

void LineBorderRenderer::addSpaces(size_t margin, std::string& line) const {
    for (size_t i = 0; i < margin; i++) {
        line += this->emptyChar;
    }
}


Content LineBorderRenderer::encapsulateContent(Content& content, std::string& title, size_t contentWidth, size_t contentHeight, EdgeDimensions& padding, EdgeDimensions& margin, EdgeDimensions& borderThickness) {
    Content newContent;/*TODO Make it so that if borderSize is 0, the border doesnt get drawn*/
    /*Upper Horizontal Line*/
    std::string line;

    this->addSpaces(margin.left, line);
    line += this->upperLeftCornerChar;

    for (size_t i = 0; i < padding.left + contentWidth + padding.right; i++) {
        if (i < title.size()) {
            line += title[i];
        } else {
            line += this->horizontalChar;
        }
    }
    line += this->upperRightCornerChar;
    this->addSpaces(margin.right, line);
    newContent.addLine(line);

    /*Middle Content*/

    for (size_t i = 0; i < padding.top; i++) {
        line = "";
        this->addSpaces(margin.left, line);
        line += this->verticalChar;
        this->addSpaces(padding.left + contentWidth + padding.right, line);
        line += this->verticalChar;
        this->addSpaces(margin.right, line);
        newContent.addLine(line);
    }
    for (size_t i = 0; i < contentHeight; i++) {
        line = "";
        this->addSpaces(margin.left, line);
        line += this->verticalChar;
        this->addSpaces(padding.left, line);
        for (size_t k = 0; k < contentWidth; k++) {
            std::string contentLine = content.getLine(i);
            if (k > contentLine.size() - 1 || contentLine.empty()) {
                line += this->emptyChar;
            } else {
                line += contentLine[k];
            }
        }
        this->addSpaces(padding.right, line);
        line += this->verticalChar;
        this->addSpaces(margin.right, line);
        newContent.addLine(line);
    }

    /*Lower Horizontal Line*/
    line = "";
    this->addSpaces(margin.left, line);
    line += this->lowerLeftCornerChar;

    for (size_t i = 0; i < padding.left + contentWidth + padding.right; i++) {
        line += this->horizontalChar;
    }
    line += this->lowerRightCornerChar;
    this->addSpaces(margin.right, line);
    newContent.addLine(line);

    return newContent;
}



