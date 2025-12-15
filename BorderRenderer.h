//
// Created by et118 on 12/3/25.
//

#ifndef SKETCH3_BORDERRENDERER_H
#define SKETCH3_BORDERRENDERER_H
#include "EdgeDimensions.h"
#include "Content.h"
#include <string>
class BorderRenderer {
public:
    virtual ~BorderRenderer() = default;
    virtual Content encapsulateContent(Content& content, std::string& title, size_t contentWidth, size_t contentHeight, EdgeDimensions& padding, EdgeDimensions& margin, EdgeDimensions& borderThickness) = 0;
};
#endif //SKETCH3_BORDERRENDERER_H