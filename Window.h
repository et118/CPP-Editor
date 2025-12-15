//
// Created by et118 on 12/2/25.
//

#ifndef SKETCH3_WINDOW_H
#define SKETCH3_WINDOW_H
#include <string>
#include "EdgeDimensions.h"
#include "BorderRenderer.h"
#include "Content.h"

class Window {
public:
    virtual ~Window();
    virtual void tick() = 0;
    virtual Content renderContent() = 0;

    Content render();

    size_t getMinTotalWidth() const;
    size_t getMinTotalHeight() const;
    size_t getMaxTotalWidth() const;
    size_t getMaxTotalHeight() const;
    size_t getTotalWidth() const;
    size_t getTotalHeight() const;
    void setMinTotalWidth(size_t width);
    void setMinTotalHeight(size_t height);
    void setMaxTotalWidth(size_t width);
    void setMaxTotalHeight(size_t height);
    void setTotalWidth(size_t width);
    void setTotalHeight(size_t height);
private:
    BorderRenderer* borderRenderer;

    EdgeDimensions padding;
    EdgeDimensions margin;
    EdgeDimensions borderThickness;

    std::string title;
protected:
    size_t contentWidth;
    size_t contentHeight;

    size_t minTotalWidth;
    size_t minTotalHeight;
    size_t maxTotalWidth;
    size_t maxTotalHeight;

    explicit Window(const std::string &title, BorderRenderer* borderRenderer, const EdgeDimensions &padding, const EdgeDimensions &margin, const EdgeDimensions &borderThickness, size_t minTotalWidth, size_t minTotalHeight, size_t maxTotalWidth, size_t maxTotalHeight);
};
#endif //SKETCH3_WINDOW_H