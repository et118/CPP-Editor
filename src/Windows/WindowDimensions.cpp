//
// Created by et118 on 04/01/2026.
//
#include "../../include/Windows/WindowDimensions.h"

WindowDimensions::WindowDimensions(Vector4D<unsigned int> borderThickness, Vector4D<unsigned int> margin, Vector4D<unsigned int> padding)
    : borderThickness(borderThickness), margin(margin), padding(padding),
     maxSize({0,0}), minSize({0,0}), contentAreaSize({0,0}) {
}

void WindowDimensions::setMaxSize(Vector2D<unsigned int> max) {
    this->maxSize = max;
}

void WindowDimensions::setMinSize(Vector2D<unsigned int> min) {
    this->minSize = min;
}

void WindowDimensions::setContentAreaSize(Vector2D<unsigned int> contentAreaSize) {
    this->contentAreaSize = contentAreaSize;
}

Vector2D<unsigned int> WindowDimensions::getMaxSize() const {
    return this->maxSize;
}

Vector2D<unsigned int> WindowDimensions::getMinSize() const {
    return this->minSize;
}

Vector2D<unsigned int> WindowDimensions::getAbsoluteMinSize() {
    unsigned int minX =
        this->borderThickness.getX() + this->borderThickness.getZ() +
        this->margin.getX() + this->margin.getZ() +
        this->padding.getX() + this->padding.getZ();
    unsigned int minY =
        this->borderThickness.getY() + this->borderThickness.getW() +
        this->margin.getY() + this->margin.getW() +
        this->padding.getY() + this->padding.getW();

    return {minX, minY};
}

Vector2D<unsigned int> &WindowDimensions::getContentAreaSize() {
    return this->contentAreaSize;
}

Vector4D<unsigned int> &WindowDimensions::getBorderThickness(){
    return this->borderThickness;
}

Vector4D<unsigned int> &WindowDimensions::getMargin(){
    return this->margin;
}

Vector4D<unsigned int> &WindowDimensions::getPadding(){
    return this->padding;
}
