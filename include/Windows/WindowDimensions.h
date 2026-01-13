//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_WINDOWDIMENSIONS_H
#define CPP_EDITOR_WINDOWDIMENSIONS_H
#include "../Util/Vector4D.h"
#include "../Util/Vector2D.h"
class WindowDimensions {
private:
    Vector4D<unsigned int> borderThickness; //Left Up Right Down
    Vector4D<unsigned int> margin;
    Vector4D<unsigned int> padding;
    Vector2D<unsigned int> maxSize;
    Vector2D<unsigned int> minSize;
    Vector2D<unsigned int> contentAreaSize;

public:
    WindowDimensions(Vector4D<unsigned int> borderThickness, Vector4D<unsigned int> margin, Vector4D<unsigned int> padding);
    Vector4D<unsigned int>& getBorderThickness();
    Vector4D<unsigned int>& getMargin();
    Vector4D<unsigned int>& getPadding();
    Vector2D<unsigned int>& getContentAreaSize();
    void setContentAreaSize(Vector2D<unsigned int> newContentAreaSize);

    Vector2D<unsigned int> getMaxSize() const;
    Vector2D<unsigned int> getMinSize() const;
    Vector2D<unsigned int> getAbsoluteMinSize();
    void setMaxSize(Vector2D<unsigned int> max);
    void setMinSize(Vector2D<unsigned int> min);

};
#endif //CPP_EDITOR_WINDOWDIMENSIONS_H