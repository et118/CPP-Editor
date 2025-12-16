//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_CONTAINER2D_H
#define CPP_EDITOR_CONTAINER2D_H
template<typename T>
class Container2D {
private:
    T width;
    T height;
public:
    Container2D(T width, T height) : width(width), height(height) {};
};
#endif //CPP_EDITOR_CONTAINER2D_H