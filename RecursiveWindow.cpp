//
// Created by et118 on 12/4/25.
//

#include "RecursiveWindow.h"
#include <iostream>

RecursiveWindow::RecursiveWindow() : Window("", nullptr, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, 0, 0, 0, 0), horizontal(true) {
}

void RecursiveWindow::addWindow(Window* window) {
    this->innerWindows.push_back(window);
}

void RecursiveWindow::tick() {
    /*Manage Window Sizes???*/
    if (this->horizontal) {
        size_t sumAllMinWidths = 0;
        for (Window* window : this->innerWindows) {
            sumAllMinWidths += window->getMinTotalWidth();
            window->setTotalWidth(window->getMinTotalWidth());
        }
        if (this->getMaxTotalWidth() != 0 && sumAllMinWidths > this->getMaxTotalWidth()) {
            /*TODO Scrollbar behaviour*/
        } else {
            for (Window* window : this->innerWindows) {
                window->setTotalHeight(this->getTotalHeight());
            }
            size_t increaseBy = std::max(static_cast<long long>(this->getTotalWidth()) - static_cast<long long>(sumAllMinWidths), 0LL);

            while (increaseBy > 0) { /*TODO Will cause infinite loop if all max height reached*/
                for (Window* window : this->innerWindows) {
                    if (window->getMaxTotalWidth() != 0 && window->getMaxTotalWidth() <= window->getTotalWidth()) continue;
                    if (increaseBy > 0) {
                        window->setTotalWidth(window->getTotalWidth() + 1);
                        increaseBy--;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    for (Window* window : this->innerWindows) {
        window->tick();
    }
}

Content RecursiveWindow::renderContent() {
    Content content;
    for (Window* window : this->innerWindows) {
        Content subContent = window->render();
        if (this->horizontal) {
            content += subContent; /*Stack lines left to right*/
        } else {
            for (size_t i = 0; i < subContent.getNumLines(); i++) {
                content.addLine(subContent.getLine(i)); /*Stack lines under eachother*/
            }
        }
    }

    return content;
}
