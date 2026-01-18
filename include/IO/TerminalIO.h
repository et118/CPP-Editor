//
// Created by et118 on 10/01/2026.
//

#ifndef CPP_EDITOR_TERMINALINPUT_H
#define CPP_EDITOR_TERMINALINPUT_H

#include <termios.h>
#include <vector>
#include "../Windows/Window.h"
#include <sys/ioctl.h>
namespace TerminalIO {
    void clearTerminal();
    struct termios takeControlOfTerminal();
    void releaseControlOfTerminal(struct termios original);
    void bindResizeCallback(void(*callback)(unsigned int, unsigned int));
    void unbindResizeCallback(void(*callback)(unsigned int, unsigned int));

    int handleWindowInput(Window* window);

    struct winsize getWindowSize();

    static bool __hasBoundResizeCallback = false;
    static std::vector<void(*)(unsigned int, unsigned int)> __resizeCallbacks;
}
#endif //CPP_EDITOR_TERMINALINPUT_H