//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_WINDOWDIMENSIONS_H
#define CPP_EDITOR_WINDOWDIMENSIONS_H
#include "../Util/Vector4D.h"
#include "../Util/Vector2D.h"
class WindowDimensions {
private:
    Vector4D<unsigned int> borderThickness;
    Vector4D<unsigned int> margin;
    Vector4D<unsigned int> padding;
    Vector2D<unsigned int> contentMaxDimensions;
};
#endif //CPP_EDITOR_WINDOWDIMENSIONS_H