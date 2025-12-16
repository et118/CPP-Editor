//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_WINDOWDIMENSIONS_H
#define CPP_EDITOR_WINDOWDIMENSIONS_H
#include "../Util/Container4D.h"
#include "../Util/Container2D.h"
class WindowDimensions {
private:
    Container4D<unsigned int> borderThickness;
    Container4D<unsigned int> margin;
    Container4D<unsigned int> padding;
    Container2D<unsigned int> contentMaxDimensions;
};
#endif //CPP_EDITOR_WINDOWDIMENSIONS_H