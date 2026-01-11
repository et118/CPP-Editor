//
// Created by et118 on 11/01/2026.
//

#ifndef CPP_EDITOR_KEYEVENT_H
#define CPP_EDITOR_KEYEVENT_H
#include <string>
struct KeyEvent {
    std::string key;
    bool ctrl = false;
    bool alt = false;
};
#endif //CPP_EDITOR_KEYEVENT_H