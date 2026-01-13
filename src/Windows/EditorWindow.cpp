//
// Created by et118 on 10/01/2026.
//
#include "../../include/Windows/EditorWindow.h"
#include "../../include/BorderRenderers/SimpleBorderRenderer.h"
#include "../../include/Util/StringUtils.h"
#include "../../include/IO/FileIO.h"

EditorWindow::EditorWindow(const std::string &path)
: Window(
        "Editor",
        {{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        new SimpleBorderRenderer(),
        std::vector<MenuItem*>{}),
        cursorPosition({0,0}), lastCursorPosition({9999,9999}), scroll({0,0}), savedCursorPositionX(0), hasOpenFile(false), isFileChanged(false), wasFileChanged(false) {
    this->openFile(path);
}
//We dont need to delete the MenuItems or borderrenderer in a destructor because when program exits since its handled automatically by the baseclass Window

void EditorWindow::openFile(const std::filesystem::path &path) {
    if (this->hasOpenFile) this->closeFile();
    Content content = FileIO::readFileAsContent(path);

    if (content.getLine(0) == "Error") {
        this->currentFileContents = content;
        return;
    }

    this->cursorPosition = {0,0};
    this->currentOpenFile = path;
    this->currentFileContents = content;
    this->currentRenderContents = content;
    this->updateTitle();

    if (!this->hasOpenFile) {
        this->addMenuItem(new MenuItem("Save", this, [](Window* window, std::string title) {
            dynamic_cast<EditorWindow*>(window)->saveFile();
        }));
        this->addMenuItem(new MenuItem("Close", this, [](Window* window, std::string title) {
            dynamic_cast<EditorWindow*>(window)->closeFile();
        }));
    }
    this->hasOpenFile = true;
}

void EditorWindow::saveFile() {
    if (!hasOpenFile) return;
    if (!FileIO::ensureParentPath(this->currentOpenFile)) { //If parent folder cant be created, fail quietly for now.
        return; //TODO We need some kind of notification system for this
    }
    if (!FileIO::writeFileAsContent(this->currentOpenFile, this->currentFileContents)) {
        return; //We failed to save
    }
    isFileChanged = false;
}

void EditorWindow::closeFile() {
    Content empty;
    this->hasOpenFile = false;
    this->isFileChanged = false;
    this->currentOpenFile = "";
    this->currentFileContents = empty;
    this->currentRenderContents = empty;
    this->clearMenuItems(); //Window baseclass handles deallocating memory
    this->updateTitle();
}

Content EditorWindow::renderContent() {
    if (hasOpenFile) {
        if (lastCursorPosition.getX() != cursorPosition.getX() || lastCursorPosition.getY() != cursorPosition.getY()) {
            currentRenderContents = currentFileContents; //Wipe previous
            std::string line = this->currentRenderContents.getLine(this->cursorPosition.getY());
            if (line == "") line = "  ";
            unsigned int numCharacters = Content::getNumCharacters(line);
            std::string newLine;
            size_t index = 0;
            while (index < numCharacters + 1) {
                if (index == this->cursorPosition.getX()) {
                    std::string character;
                    if (index == numCharacters) {
                        character = " ";
                    } else {
                        character = Content::getCharacter(line, index);
                    }
                    newLine += StringUtils::to_inverted(character);
                    if (index >= numCharacters - 1) newLine += " ";
                } else {
                    newLine += Content::getCharacter(line, index);
                }
                index++;
            }
            currentRenderContents.changeLine(this->cursorPosition.getY(), newLine);
        }
    }

    Content newContent;
    for (size_t y = scroll.getY(); y < this->currentRenderContents.getNumLines(); y++) {
        std::string currentLine = this->currentRenderContents.getLine(y);
        std::string newLine;
        for (size_t x = scroll.getX(); x < Content::getNumCharacters(currentLine); x++) {
            newLine += Content::getCharacter(currentLine, x);
        }
        newContent.addLine(newLine);
    }

    lastCursorPosition = cursorPosition;
    return newContent;
}

void EditorWindow::moveCursorUp() {
    if (this->cursorPosition.getY() >= 1) {
        std::string aboveLine = this->currentFileContents.getLine(this->cursorPosition.getY() - 1);
        size_t numCharacters = Content::getNumCharacters(aboveLine);
        if (numCharacters < savedCursorPositionX) {
            this->cursorPosition.setX(numCharacters - (numCharacters == 0 ? 0 : 1));
        } else if (numCharacters > savedCursorPositionX) {
            this->cursorPosition.setX(this->savedCursorPositionX);
        }
        this->cursorPosition.setY(this->cursorPosition.getY() - 1);
    } else {
        this->cursorPosition = {0,0};
    }
    updateScroll();
}

void EditorWindow::moveCursorDown() {
    if (this->cursorPosition.getY() < this->currentFileContents.getNumLines()) {
        std::string belowLine = this->currentFileContents.getLine(this->cursorPosition.getY() + 1);
        size_t numCharacters = Content::getNumCharacters(belowLine);
        if (numCharacters < this->savedCursorPositionX) {
            this->cursorPosition.setX(numCharacters - (numCharacters == 0 ? 0 : 1));
        } else if (numCharacters > this->savedCursorPositionX) {
            this->cursorPosition.setX(this->savedCursorPositionX);
        }
        this->cursorPosition.setY(this->cursorPosition.getY() + 1);
    }
    updateScroll();
}

void EditorWindow::moveCursorLeft() {
    if (this->cursorPosition.getX() == 0) {
        if (this->cursorPosition.getY() > 0) {
            this->moveCursorUp();
            this->cursorPosition.setX(Content::getNumCharacters(this->currentFileContents.getLine(this->cursorPosition.getY()))); //Top of previous line
        }
    } else {
        this->cursorPosition.setX(this->cursorPosition.getX() - 1);
    }
    savedCursorPositionX = this->cursorPosition.getX();
    updateScroll();
}

void EditorWindow::moveCursorRight() {
    if (this->cursorPosition.getX() >= Content::getNumCharacters(this->currentFileContents.getLine(this->cursorPosition.getY()))) {
        this->moveCursorDown();
        this->cursorPosition.setX(0);
    } else {
        this->cursorPosition.setX(this->cursorPosition.getX() + 1);
    }
    savedCursorPositionX = this->cursorPosition.getX();
    updateScroll();
}

void EditorWindow::updateScroll() {
    //Up
    if (scroll.getY() > cursorPosition.getY()) {
        scroll.setY(cursorPosition.getY());
    }
    //Down
    if (cursorPosition.getY() > this->windowDimensions.getContentAreaSize().getY() - 1 + scroll.getY()) {
        scroll.setY(cursorPosition.getY() - (this->windowDimensions.getContentAreaSize().getY()));
    }
    //Left
    if (scroll.getX() > 0 && cursorPosition.getX() < scroll.getX() + 1) {
        scroll.setX(cursorPosition.getX());
    }
    //Right
    if (cursorPosition.getX() > this->windowDimensions.getContentAreaSize().getX() - 1 + scroll.getX()) {
        scroll.setX(cursorPosition.getX() - this->windowDimensions.getContentAreaSize().getX());
    }
}

void EditorWindow::updateTitle() {
    std::string newTitle = "Editor";
    if (this->hasOpenFile) {
        newTitle += " (" + StringUtils::to_bold(this->currentOpenFile.filename().string());
        if (this->isFileChanged) {
            newTitle += "*";
        }
        newTitle += ")";
    }
    this->title = newTitle;
}

std::filesystem::path EditorWindow::getCurrentOpenFile() {
    return this->currentOpenFile;
}

bool EditorWindow::onKeyboardInput(KeyEvent& event) {
    if (Window::onKeyboardInput(event)) return true;

    if (event.key == "\x1B[A") { //Up arrow
        this->moveCursorUp();
    } else if (event.key == "\x1B[B") { //Down arrow
        this->moveCursorDown();
    } else if (event.key == "\x1B[C") { //Right arrow
        this->moveCursorRight();
    } else if (event.key == "\x1B[D") { //Left arrow
        this->moveCursorLeft();
    }

    if (event.ctrl && event.key == "S") {
        this->saveFile();
    }

    if (event.ctrl && event.key == "J") { //Enter button
        Content newFileContents;
        for (size_t i = 0; i < this->currentFileContents.getNumLines(); i++) {
            if (i == this->cursorPosition.getY()) {
                std::string left;
                std::string right;
                for (size_t j = 0; j < Content::getNumCharacters(currentFileContents.getLine(i)); j++) {
                    std::string character = Content::getCharacter(currentFileContents.getLine(i),j);
                    if (j < this->cursorPosition.getX()) {
                        left += character;
                    } else {
                        right += character;
                    }
                }
                newFileContents.addLine(left);
                newFileContents.addLine(right);
            } else {
                newFileContents.addLine(currentFileContents.getLine(i));
            }
        }
        if (this->currentFileContents.getNumLines() == this->cursorPosition.getY()) {
            newFileContents.addLine("");
        }
        this->currentFileContents = newFileContents;
        cursorPosition = {0, cursorPosition.getY()};
        savedCursorPositionX = 0;
        this->moveCursorDown();
        scroll = {0, scroll.getY()};
        isFileChanged = true;
    }

    //Normal input
    if (!event.ctrl && !event.alt && !event.key.starts_with('\x1B')) {
        std::string currentLine = currentFileContents.getLine(this->cursorPosition.getY());
        size_t numCharacters = Content::getNumCharacters(currentLine);
        std::string newLine;
        if (event.key == "\x7F") { //Backspace
            if (currentLine.empty()) {
                if (this->cursorPosition.getY() != this->currentFileContents.getNumLines()) {
                    currentFileContents.removeLine(this->cursorPosition.getY());
                }
                this->moveCursorLeft();
            } else {
                for (size_t i = 0; i < numCharacters; i++) {
                    if (i + 1 != this->cursorPosition.getX()) {
                        newLine += Content::getCharacter(currentLine, i);
                    }
                }
                currentFileContents.changeLine(this->cursorPosition.getY(), newLine);
                this->moveCursorLeft();
            }
        } else {
            size_t num = Content::getNumCharacters(event.key);
            for (size_t i = 0; i <= numCharacters; i++) {
                if (i == this->cursorPosition.getX()) {
                    for (char c : event.key) {
                        newLine += c;
                    }
                    //if you want insert mode writing you can add: "i += num" here
                    numCharacters += num;
                }
                newLine += Content::getCharacter(currentLine, i);
            }
            currentFileContents.changeLine(this->cursorPosition.getY(), newLine);
            for (size_t i = 0; i < num; i++) {
                this->moveCursorRight();
            }
        }
        isFileChanged = true;
    }
    return true;
}

void EditorWindow::tick() {
    if (wasFileChanged != isFileChanged) {
        wasFileChanged = isFileChanged;
        this->updateTitle();
    }
    Window::tick();
}
