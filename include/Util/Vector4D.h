//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_CONTAINER4D_H
#define CPP_EDITOR_CONTAINER4D_H
template<typename T>
class Vector4D {
private:
    T top;
    T bottom;
    T left;
    T right;
public:
    Vector4D(T top, T bottom, T left, T right) : top(top), bottom(bottom), left(left), right(right) {};
};
#endif //CPP_EDITOR_CONTAINER4D_H