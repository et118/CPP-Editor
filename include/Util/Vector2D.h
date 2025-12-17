//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_CONTAINER2D_H
#define CPP_EDITOR_CONTAINER2D_H
template<typename T>
class Vector2D {
private:
    T x;
    T y;
public:
    Vector2D(T x, T y) : x(x), y(y) {};
    void update(T x, T y);
    void updateX(T x);
    void updateY(T y);
    T getX();
    T getY();
};
#endif //CPP_EDITOR_CONTAINER2D_H