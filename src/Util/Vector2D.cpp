//
// Created by et118 on 12/17/25.
//
#include "../../include/Util/Vector2D.h"

template<typename T>
void Vector2D<T>::update(T x, T y) {
    this->x = x;
    this->y = y;
}

template<typename T>
void Vector2D<T>::updateX(T x) {
    this->x = x;
}


template<typename T>
void Vector2D<T>::updateY(T y) {
    this->y = y;
}

template<typename T>
T Vector2D<T>::getX() {
    return this->x;
}

template<typename T>
T Vector2D<T>::getY() {
    return this->y;
}


