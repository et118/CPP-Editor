//
// Created by et118 on 10/01/2026.
//
#include "../../include/IO/TerminalIO.h"
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "../../include/IO/KeyEvent.h"

namespace TerminalIO {
    void clearTerminal() {
        std::cout << "\x1B[3J\x1B[2J\x1B[H" << std::flush;
        //std::cout << "\x1B[2J" << "\x1B[H" << std::flush;
    }

    void releaseControlOfTerminal(struct termios original) {
        //Stop tracking input
        std::cout << "\x1B[?1003l";
        std::cout << "\x1B[?1006l" << std::flush;

        //Clear input buffer
        tcflush(STDIN_FILENO, TCIFLUSH);

        //Enable input echo
        tcsetattr(STDIN_FILENO, TCSANOW, &original);

        //Show cursor
        std::cout << "\x1B[?25h" << std::flush;
    }

    struct termios takeControlOfTerminal() {
        struct termios orig, raw;
        tcgetattr(STDIN_FILENO, &orig);
        raw = orig;

        raw.c_lflag &= ~(ECHO | ICANON); //Disable echo and waiting for newline
        raw.c_lflag &= ~ISIG; //Disable Ctrl+C and Ctrl+Z
        raw.c_iflag &= ~(IXON | IXOFF); //Disable Ctrl+S and Ctrl+Q
        //raw.c_iflag &= ~(ICRNL);// | INLCR | IGNCR);
        //raw.c_oflag &= ~(ONLCR | OCRNL);

        //Enable polling mode. Nonblocking read() call. Returns 0 if no data in buffer.
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);

        //Clear screen
        clearTerminal();

        //Hide cursor
        std::cout << "\x1B[?25l" << std::flush;

        //Start tracking dragging, moving, clicking and tracking
        std::cout << "\x1B[?1003h";
        std::cout << "\x1B[?1006h" << std::flush; //Enable extended coordinates SGR tracking
        return orig;
    }

    int handleWindowInput(Window *window) {
        std::string escapeSequence;
        bool inEscapeSequence = false;
        char c;
        while (read(STDIN_FILENO, &c, 1) == 1) {
            //Normal keys
            if (!inEscapeSequence) {
                if (c == '\x1B') { // Escape starts a sequence
                    escapeSequence.clear();
                    escapeSequence.push_back(c);
                    inEscapeSequence = true;
                    continue;
                }
                KeyEvent event;
                if (c >= 0x01 && c <= 0x1A) { // Ctrl+A..Ctrl+Z
                    event.ctrl = true;
                    event.key = std::string(1, c + 'A' - 1);
                    if (event.key == "Q") return 1; //quit if detected CTRL + Q
                    window->onKeyboardInput(event);
                    continue;
                }
                event.key = std::string(1,c);
                window->onKeyboardInput(event);
                continue;
            }

            escapeSequence.push_back(c);

            // Mouse events (SGR)
            if (escapeSequence.size() >= 6 && escapeSequence[0] == '\x1B' && escapeSequence[1] == '[' && escapeSequence[2] == '<') {
                if (c == 'M' || c == 'm') {
                    unsigned int btn, x, y;
                    char type;

                    if (sscanf(escapeSequence.c_str(), "\x1B[<%u;%u;%u%c", &btn, &x, &y, &type) == 4) {
                        x = x - 1; // 0-based
                        y = y - 1;
                        bool rightClick = btn & 2;

                        bool isMove = btn & 32;
                        bool pressed = (type == 'M');

                        if (isMove) {
                            window->onMouseMove(x, y);
                            //std::cout << "MOVE: " << x << ", " << y << std::endl;
                        } else if (pressed) {
                            window->onMouseDown(x,y,rightClick);
                            //std::cout << "DOWN: " << x << ", " << y << " " << rightClick << std::endl;
                        } else {
                            window->onMouseUp(x,y,rightClick);
                            //std::cout << "UP: " << x << ", " << y << " " << rightClick << std::endl;
                        }
                    }
                    inEscapeSequence = false;
                    escapeSequence.clear();
                }
                continue;
            }
            // ALT + key (ESC + printable)
            if (escapeSequence.size() == 2 &&
                    escapeSequence[0] == '\x1B' &&
                    escapeSequence[1] != '[' && // <-- prevent false positive
                    std::isprint(static_cast<unsigned char>(escapeSequence[1]))) {
                KeyEvent event;
                event.alt = true;
                event.ctrl = false;
                event.key = std::string(1, escapeSequence[1]);
                //std::cout << "ALT: " << event.key << std::endl;
                window->onKeyboardInput(event);
                inEscapeSequence = false;
                escapeSequence.clear();
                continue;
            }



            // CSI / arrow keys (optional MVP)
            if (std::isalpha(static_cast<unsigned char>(c)) || c == '~') {
                KeyEvent event;
                event.key = escapeSequence; // raw sequence
                //std::cout << "CSI/Arrow: " << event.key << std::endl;
                window->onKeyboardInput(event);
                inEscapeSequence = false;
                escapeSequence.clear();
            }
        }
        return 0;
    }

    void bindResizeCallback(void (*callback)(unsigned int, unsigned int)) {
        __resizeCallbacks.push_back(callback);
        if (!__hasBoundResizeCallback) {
            __hasBoundResizeCallback = true;
            signal(SIGWINCH, [](int) -> void { //Subscribe to terminal resize signal
                struct winsize w;
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); //ask for window size
                for (auto callback : __resizeCallbacks) {
                    callback(w.ws_col, w.ws_row);
                }
            });
        }
    }

    void unbindResizeCallback(void (*callback)(unsigned int, unsigned int)) {
        for (size_t i = 0; i < __resizeCallbacks.size(); i++) {
            if (__resizeCallbacks.at(i) == callback) {
                __resizeCallbacks.erase(__resizeCallbacks.begin() + i - 1);
                if (__resizeCallbacks.empty()) signal(SIGWINCH, SIG_DFL); //Unsubscribe from signal if no more callbacks (just incase, not necessary i think)
                return;
            }
        }
    }
}

