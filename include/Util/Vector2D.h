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
    void update(T x, T y) {
        this->x = x;
        this->y = y;
    };
    void updateX(T x) {
        this->x = x;
    };
    void updateY(T y) {
        this->y = y;
    };
    T getX() {return this->x;};
    T getY() {return this->y;};
};

#endif //CPP_EDITOR_CONTAINER2D_H