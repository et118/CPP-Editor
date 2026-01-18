//
// Created by et118 on 12/16/25.
//

#ifndef CPP_EDITOR_CONTAINER4D_H
#define CPP_EDITOR_CONTAINER4D_H
template<typename T>
class Vector4D {
private:
    T x;
    T y;
    T z;
    T w;
public:
    Vector4D(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
    T getX() { return x; }
    T getY() { return y; }
    T getZ() { return z; }
    T getW() { return w; }
    //No setters yet because i havent needed them
};
#endif //CPP_EDITOR_CONTAINER4D_H