//
// Created by et118 on 04/01/2026.
//
#include "../../include/Windows/RecursiveWindow.h"

#include <iostream>

#include "../../include/IO/TerminalIO.h"

RecursiveWindow::RecursiveWindow() : Window(
    "",
    {{0,0,0,0},{0,0,0,0},{0,0,0,0}},
    nullptr,
    std::vector<MenuItem*>()) {
    this->horizontal = true;
    this->extraPadding = 0;
    this->lastFocusedWindow = nullptr;
}

void RecursiveWindow::addWindow(Window *window) {
    this->innerWindows.emplace_back(window);
}

Content RecursiveWindow::renderContent() {
    Content content;
    size_t maxWidth = 0;
    for (Window* window : this->innerWindows) {
        Content subContent = window->render();

        if (this->horizontal) {
            maxWidth += window->windowDimensions.getContentAreaSize().getX();
            for (size_t i = 0; i < subContent.getNumLines(); i++) {
                content.changeLine(i, content.getLine(i) + subContent.getLine(i));
            }
        } else {
            if (window->windowDimensions.getContentAreaSize().getX() > maxWidth) {maxWidth = window->windowDimensions.getContentAreaSize().getX();}
            for (size_t i = 0; i < subContent.getNumLines(); i++) {
                content.addLine(subContent.getLine(i));
            }
        }

    }
    if (this->extraPadding > 0) {
        if (this->horizontal) {
            std::string spaces(this->extraPadding,' ');
            for (size_t i = 0; i < content.getNumLines(); i++) {
                content.changeLine(i, content.getLine(i) + spaces);
            }
        } else {
            std::string spaces(this->windowDimensions.getContentAreaSize().getX(),' ');
            for (size_t i = 0; i < this->extraPadding; i++) {
                content.addLine(spaces);
            }
        }

    }

    /*Cut off content if its too large somehow. Useful now when i dont have scrollbar implemented*/
    for (size_t i = content.getNumLines() - 1; i > 0; i--) {
        if (i >= this->windowDimensions.getContentAreaSize().getY()) {
            content.removeLine(i);
        } else if (maxWidth > this->windowDimensions.getContentAreaSize().getX()){
            content.changeLine(i, content.getLine(i).substr(0,this->windowDimensions.getContentAreaSize().getX()));
        }
    }
    return content;
}

int RecursiveWindow::isInsideInnerWindow(unsigned int x, unsigned int y, unsigned int* relativeX, unsigned int* relativeY) const {
    unsigned int totalX = this->horizontal ? 0 : x;
    unsigned int totalY = this->horizontal ? y : 0;
    int index = 0;
    for (Window* window : this->innerWindows) {
        if (x >= totalX && x < totalX + window->windowDimensions.getContentAreaSize().getX() + window->windowDimensions.getAbsoluteMinSize().getX() &&
            y >= totalY && y < totalY + window->windowDimensions.getContentAreaSize().getY() + window->windowDimensions.getAbsoluteMinSize().getY()) {
            if (relativeX) *relativeX = x - (this->horizontal ? totalX : 0);
            if (relativeY) *relativeY = y - (this->horizontal ? 0 : totalY);
            return index;
            }
        if (this->horizontal) {
            totalX += window->windowDimensions.getContentAreaSize().getX() + window->windowDimensions.getAbsoluteMinSize().getX();
        } else {
            totalY += window->windowDimensions.getContentAreaSize().getY() + window->windowDimensions.getAbsoluteMinSize().getY();
        }
        index++;
    }
    return -1;
}

bool RecursiveWindow::onMouseDown(unsigned int x, unsigned int y, bool rightClick){
    if (Window::onMouseDown(x, y, rightClick)) return true; //Let base window manage some variables for mouse pos. Consume
    unsigned int relativeX = 0;
    unsigned int relativeY = 0;
    if (int index = this->isInsideInnerWindow(x,y, &relativeX, &relativeY); index != -1) {
        this->innerWindows.at(index)->onMouseDown(relativeX, relativeY, rightClick);
    }
    return true;
}
bool RecursiveWindow::onMouseMove(unsigned int x, unsigned int y){
    if (Window::onMouseMove(x, y)) return true;
    unsigned int relativeX = 0;
    unsigned int relativeY = 0;
    if (int index = this->isInsideInnerWindow(x,y, &relativeX, &relativeY); index != -1) {
        Window* window = this->innerWindows.at(index);
        if (this->lastFocusedWindow && this->lastFocusedWindow != window) {
            this->lastFocusedWindow->setFocused(false);
            this->lastFocusedWindow->onMouseUp(0,0,false);
            this->lastFocusedWindow->onMouseUp(0,0,true);
            window->setFocused(true);
            this->lastFocusedWindow = window;
        }
        window->onMouseMove(relativeX, relativeY);
    }
    return true;
}
bool RecursiveWindow::onMouseUp(unsigned int x, unsigned int y, bool rightClick){
    if (Window::onMouseUp(x, y, rightClick)) return true;
    unsigned int relativeX = 0;
    unsigned int relativeY = 0;
    if (int index = this->isInsideInnerWindow(x,y, &relativeX, &relativeY); index != -1) {
        this->innerWindows.at(index)->onMouseUp(relativeX, relativeY, rightClick);
    }
    return true;
}
bool RecursiveWindow::onKeyboardInput(KeyEvent& event) {
    if (int index = this->isInsideInnerWindow(this->currentMousePos.getX(),this->currentMousePos.getY(), nullptr, nullptr); index != -1) {
        this->innerWindows.at(index)->onKeyboardInput(event);
    }
    if (this->innerWindows.size() == 1) {
        if (Window::onKeyboardInput(event)) return true; // Ignore this for deleting inner windows first
    }
    return true;
}

void RecursiveWindow::tick() {
    this->extraPadding = 0;
    Vector2D<unsigned int> availableSpace = this->windowDimensions.getContentAreaSize();
    unsigned int contentArea;
    unsigned int sumMin = 0;
    if (this->horizontal) {
        contentArea = availableSpace.getX();
    } else {
        contentArea = availableSpace.getY();
    }
    int index = 0;
    for (Window* window : this->innerWindows) {
        if (!window->isAlive()) {
            TerminalIO::clearTerminal();
            this->innerWindows.erase(this->innerWindows.begin() + index);
            continue;
        }
        index++;

        //sumMin += this->horizontal ? window->windowDimensions.getAbsoluteMinSize().getX() : window->windowDimensions.getAbsoluteMinSize().getY();
        //TODO warning, this ignores their maxheight/maxwidth

        //Setting opposite axis to fixed size
        unsigned int absMinSize = this->horizontal ? window->windowDimensions.getAbsoluteMinSize().getY() : window->windowDimensions.getAbsoluteMinSize().getX();
        unsigned int contentAreaMin = 0;
        if ((this->horizontal ? availableSpace.getY() : availableSpace.getX()) > absMinSize) {
            contentAreaMin = (this->horizontal ? availableSpace.getY() : availableSpace.getX()) - absMinSize;
        }
        unsigned int absWindowMin = this->horizontal ? window->windowDimensions.getAbsoluteMinSize().getX() : window->windowDimensions.getAbsoluteMinSize().getY();
        unsigned int windowMin = this->horizontal ? window->windowDimensions.getMinSize().getX() : window->windowDimensions.getMinSize().getY();
        if (windowMin <= absWindowMin) {
            windowMin = 0;
            sumMin += absWindowMin;
        } else {
            sumMin += windowMin;

            windowMin -= absWindowMin;
        }
        //Setting axis minimum
        window->windowDimensions.setContentAreaSize({ this->horizontal ? windowMin : contentAreaMin, this->horizontal ? contentAreaMin : windowMin});
    }

    if (sumMin > contentArea) {
        /*TODO Scrollbar (thought right now it will just cut off)*/
    } else {
        unsigned int toIncrease = 0;
        if (sumMin < contentArea) {
            toIncrease = contentArea - sumMin;
        }
        //unsigned int smallest = 0u - 1; //Start at the highest possible
        while (toIncrease > 0) {
            bool stuck = true;
            unsigned int smallest = 0u - 1u;
            for (Window* window : this->innerWindows) {
                unsigned int contentAreaSize = this->horizontal ? window->windowDimensions.getContentAreaSize().getX() : window->windowDimensions.getContentAreaSize().getY();
                unsigned int absWindowMin = this->horizontal ? window->windowDimensions.getAbsoluteMinSize().getX() : window->windowDimensions.getAbsoluteMinSize().getY();
                unsigned int maxSize = this->horizontal ? window->windowDimensions.getMaxSize().getX() : window->windowDimensions.getMaxSize().getY();
                if ((maxSize == 0 || (contentAreaSize + absWindowMin < maxSize )) && contentAreaSize < smallest) smallest = contentAreaSize;
            }
            for (Window* window : this->innerWindows) {
                if ((this->horizontal ? window->windowDimensions.getContentAreaSize().getX() : window->windowDimensions.getContentAreaSize().getY()) != smallest) continue;
                unsigned int maxSize = this->horizontal ? window->windowDimensions.getMaxSize().getX() : window->windowDimensions.getMaxSize().getY();
                //unsigned int minSize = this->horizontal ? window->windowDimensions.getMinSize().getX() : window->windowDimensions.getMinSize().getY();
                if (maxSize != 0 && maxSize <= (this->horizontal ? window->windowDimensions.getContentAreaSize().getX() + window->windowDimensions.getAbsoluteMinSize().getX() : window->windowDimensions.getContentAreaSize().getY() + window->windowDimensions.getAbsoluteMinSize().getY())) continue;
                //if (minSize != 0 && (this->horizontal ? window->windowDimensions.getContentAreaSize().getX() + window->windowDimensions.getAbsoluteMinSize().getX() : window->windowDimensions.getContentAreaSize().getY() + window->windowDimensions.getAbsoluteMinSize().getY()) >= (this->horizontal ? window->windowDimensions.getMinSize().getX() : window->windowDimensions.getMinSize().getY())) continue;
                if (toIncrease > 0) {
                    window->windowDimensions.setContentAreaSize({window->windowDimensions.getContentAreaSize().getX() + (this->horizontal ? 1 : 0), window->windowDimensions.getContentAreaSize().getY() + (this->horizontal ? 0 : 1)});
                    toIncrease--;
                    stuck = false;
                } else break;
            }
            if (stuck) {extraPadding = toIncrease;break;} //TODO happens if all max width are reached and we need to increase more
        }
    }

    for (Window* window : this->innerWindows) {
        window->tick();
    }
}