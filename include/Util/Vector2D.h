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
    void update(T newX, T newY) {
        this->x = newX;
        this->y = newY;
    };
    void setX(T newX) {
        this->x = newX;
    };
    void setY(T newY) {
        this->y = newY;
    };
    T getX() {return this->x;};
    T getY() {return this->y;};
};

#endif //CPP_EDITOR_CONTAINER2D_H