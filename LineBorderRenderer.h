//
// Created by et118 on 12/3/25.
//

#ifndef SKETCH3_LINEBORDERRENDERER_H
#define SKETCH3_LINEBORDERRENDERER_H
#include "EdgeDimensions.h"
#include "BorderRenderer.h"
#include "Window.h"
#include <string>
class LineBorderRenderer : public BorderRenderer{
public:
    enum BorderType {
        Square,
        Smooth,
        Solid
    };
private:
    BorderType type;


    std::string emptyChar = " ";
    std::string verticalChar;
    std::string horizontalChar;
    std::string upperLeftCornerChar;
    std::string upperRightCornerChar;
    std::string lowerLeftCornerChar;
    std::string lowerRightCornerChar;

    std::string mergeRight;
    std::string mergeLeft;
    std::string mergeTop;
    std::string mergeBottom;

    void addSpaces(size_t margin, std::string& line) const;

public:

    explicit LineBorderRenderer(BorderType borderType = Square);
    Content encapsulateContent(Content& content, std::string& title, size_t contentWidth, size_t contentHeight, EdgeDimensions& padding, EdgeDimensions& margin, EdgeDimensions& borderThickness) override;
};
#endif //SKETCH3_LINEBORDERRENDERER_H