//
// Created by et118 on 12/17/25.
//

#ifndef CPP_EDITOR_BORDERRENDERER_H
#define CPP_EDITOR_BORDERRENDERER_H
#include "../Util/Content.h"
#include "../Windows/WindowDimensions.h"
#include "MenuItem.h"
#include <string>
#include <vector>
class BorderRenderer {
public:
    virtual ~BorderRenderer() = default;
    virtual Content encapsulateContent(Content& content, std::string& title, std::vector<MenuItem*>& menuItems, bool hovered, WindowDimensions& dimensions, unsigned int mouseX, unsigned int mouseY) = 0;
};
#endif //CPP_EDITOR_BORDERRENDERER_H