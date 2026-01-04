//
// Created by et118 on 04/01/2026.
//
#include "../../include/Windows/WindowDimensions.h"

Vector4D<unsigned int> &WindowDimensions::getBorderThickness() {
    return this->borderThickness;
}

Vector2D<unsigned int> &WindowDimensions::getContentMaxDimensions() {
    return this->contentDimensions;
}

Vector4D<unsigned int> &WindowDimensions::getMargin() {
    return this->margin;
}

Vector4D<unsigned int> &WindowDimensions::getPadding() {
    return this->padding;
}
