//
// Created by et118 on 12/2/25.
//

#include "Window.h"
Window::Window(const std::string &title, BorderRenderer* borderRenderer, const EdgeDimensions &padding, const EdgeDimensions &margin, const EdgeDimensions &borderThickness, size_t minTotalWidth, size_t minTotalHeight, size_t maxTotalWidth, size_t maxTotalHeight):
      borderRenderer(borderRenderer),
      padding(padding),
      margin(margin),
      borderThickness(borderThickness),
      title(title),
      contentWidth(0),
      contentHeight(0),
      minTotalWidth(minTotalWidth),
      minTotalHeight(minTotalHeight),
      maxTotalWidth(maxTotalWidth),
      maxTotalHeight(maxTotalHeight)
{}

Window::~Window() {
      delete this->borderRenderer;
}

Content Window::render() {
      Content content = this->renderContent();
      if (this->borderRenderer != nullptr) {
            content = this->borderRenderer->encapsulateContent(content, this->title, this->contentWidth, this->contentHeight, this->padding, this->margin, this->borderThickness);
      }
      return content;
}

size_t Window::getMaxTotalHeight() const {
      return this->maxTotalHeight;
}

size_t Window::getMaxTotalWidth() const {
      return this->maxTotalWidth;
}

size_t Window::getMinTotalHeight() const {
      return this->minTotalHeight;
}


size_t Window::getMinTotalWidth() const {
      return this->minTotalWidth;
}

void Window::setMaxTotalHeight(const size_t height) {
      this->maxTotalHeight = height;
}

void Window::setMaxTotalWidth(const size_t width) {
      this->maxTotalWidth = width;
}

void Window::setMinTotalHeight(const size_t height) {
      this->minTotalHeight = height;
}

void Window::setMinTotalWidth(const size_t width) {
      this->minTotalWidth = width;
}

size_t Window::getTotalHeight() const {
      return this->contentHeight
      + this->padding.top
      + this->margin.top
      + this->borderThickness.top
      + this->padding.bottom
      + this->margin.bottom
      + this->borderThickness.bottom;
}

size_t Window::getTotalWidth() const {
      return this->contentWidth
      + this->padding.left
      + this->margin.left
      + this->borderThickness.left
      + this->padding.right
      + this->margin.right
      + this->borderThickness.right;
}

void Window::setTotalHeight(const size_t height) {

      this->contentHeight = std::max(static_cast<long long>(height)
      - static_cast<long long>(this->padding.top)
      - static_cast<long long>(this->margin.top)
      - static_cast<long long>(this->borderThickness.top)
      - static_cast<long long>(this->padding.bottom)
      - static_cast<long long>(this->margin.bottom)
      - static_cast<long long>(this->borderThickness.bottom), 0LL);
}

void Window::setTotalWidth(const size_t width) {
      this->contentWidth = std::max(static_cast<long long>(width)
      - static_cast<long long>(this->padding.left)
      - static_cast<long long>(this->margin.left)
      - static_cast<long long>(this->borderThickness.left)
      - static_cast<long long>(this->padding.right)
      - static_cast<long long>(this->margin.right)
      - static_cast<long long>(this->borderThickness.right), 0LL);
}

