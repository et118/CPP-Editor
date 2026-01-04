//
// Created by et118 on 04/01/2026.
//

#ifndef CPP_EDITOR_SIMPLEBORDERRENDERER_H
#define CPP_EDITOR_SIMPLEBORDERRENDERER_H
#include "../BorderRenderers/BorderRenderer.h"
class SimpleBorderRenderer : public BorderRenderer {
private:
    std::string emptyChar = " ";
    std::string verticalChar = "│";
    std::string horizontalChar = "─";
    std::string upperLeftCornerChar = "┌";
    std::string upperRightCornerChar = "┐";
    std::string lowerLeftCornerChar = "└";
    std::string lowerRightCornerChar = "┘";

    void addSpaces(size_t margin, std::string& line) const;
public:
    Content encapsulateContent(Content& content, std::string& title, std::vector<MenuItem*>& menuItems, bool hovered, WindowDimensions& dimensions, unsigned int mouseX, unsigned int mouseY) override;
};
#endif //CPP_EDITOR_SIMPLEBORDERRENDERER_H