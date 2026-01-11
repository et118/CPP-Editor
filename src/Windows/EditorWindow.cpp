//
// Created by et118 on 10/01/2026.
//
#include "../../include/Windows/EditorWindow.h"
#include "../../include/BorderRenderers/SimpleBorderRenderer.h"
#include <fstream>
#include <iostream>
#include "../../include/Util/StringUtils.h"

EditorWindow::EditorWindow(const std::string &path)
: Window(
        "Editor",
        {{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        new SimpleBorderRenderer(),
        std::vector<MenuItem*>{}), cursorPosition({0,0}), lastCursorPosition({9999,9999}), savedCursorPositionX(0), hasOpenFile(false) {
    this->openFile(path);
}

void EditorWindow::openFile(const std::filesystem::path &path) {
    Content content;
    std::ifstream file;
    file.open(path);
    if (!file.is_open() || std::filesystem::is_directory(path)) {
        this->currentFileContents = content;
        this->hasOpenFile = false;
        return;
    }
    this->hasOpenFile = true;
    this->cursorPosition = {0,0};

    this->currentOpenFile = path;
    this->title = "Editor (" + StringUtils::to_bold(this->currentOpenFile.filename().string()) + ")";
    for (std::string line; std::getline(file, line);) { //Thanks https://stackoverflow.com/questions/66927431/why-my-getline-does-not-read-empty-lines-of-a-file
        if (!line.empty() && line.back() == '\r') line.resize(line.size() - 1);
        content.addLine(line);
    }
    file.close();
    this->currentFileContents = content;
    this->currentRenderContents = content;

    /*TODO add menuoption when a file is opened, for save/close. Dynamic memory*/
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
    lastCursorPosition = cursorPosition;
    return this->currentRenderContents;
}

void EditorWindow::moveCursorUp() {
    if (this->cursorPosition.getY() >= 1) {
        std::string aboveLine = this->currentFileContents.getLine(this->cursorPosition.getY() - 1);
        size_t numCharacters = Content::getNumCharacters(aboveLine);
        if (numCharacters < savedCursorPositionX) {
            this->cursorPosition.updateX(numCharacters - (numCharacters == 0 ? 0 : 1));
        } else if (numCharacters > savedCursorPositionX) {
            this->cursorPosition.updateX(this->savedCursorPositionX);
        }
        this->cursorPosition.updateY(this->cursorPosition.getY() - 1);
    } else {
        this->cursorPosition = {0,0};
    }
}

void EditorWindow::moveCursorDown() {
    if (this->cursorPosition.getY() < this->currentFileContents.getNumLines()) {
        std::string belowLine = this->currentFileContents.getLine(this->cursorPosition.getY() + 1);
        size_t numCharacters = Content::getNumCharacters(belowLine);
        if (numCharacters < this->savedCursorPositionX) {
            this->cursorPosition.updateX(numCharacters);
        } else if (numCharacters > this->savedCursorPositionX) {
            this->cursorPosition.updateX(this->savedCursorPositionX);
        }
        this->cursorPosition.updateY(this->cursorPosition.getY() + 1);
    }
}

void EditorWindow::moveCursorLeft() {
    if (this->cursorPosition.getX() == 0) {
        if (this->cursorPosition.getY() > 0) {
            this->moveCursorUp();
            this->cursorPosition.updateX(Content::getNumCharacters(this->currentFileContents.getLine(this->cursorPosition.getY()))); //Top of previous line
        }
    } else {
        this->cursorPosition.updateX(this->cursorPosition.getX() - 1);
    }
    savedCursorPositionX = this->cursorPosition.getX();
}

void EditorWindow::moveCursorRight() {
    if (this->cursorPosition.getX() >= Content::getNumCharacters(this->currentFileContents.getLine(this->cursorPosition.getY()))) {
        this->moveCursorDown();
        this->cursorPosition.updateX(0);
    } else {
        this->cursorPosition.updateX(this->cursorPosition.getX() + 1);
    }
    savedCursorPositionX = this->cursorPosition.getX();
}

bool EditorWindow::onKeyboardInput(KeyEvent& event) {
    if (Window::onKeyboardInput(event)) return true;

    if (event.key == "\x1B[A") { //Up
        this->moveCursorUp();
    } else if (event.key == "\x1B[B") { //Down
        this->moveCursorDown();
    } else if (event.key == "\x1B[C") { //Right
        this->moveCursorRight();
    } else if (event.key == "\x1B[D") { //Left
        this->moveCursorLeft();
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
        this->currentFileContents = newFileContents;
        cursorPosition = {0, cursorPosition.getY() + 1};
        savedCursorPositionX = 0;
    }

    //Normal input
    if (!event.ctrl && !event.alt && !event.key.starts_with('\x1B')) {
        std::string currentLine = currentFileContents.getLine(this->cursorPosition.getY());
        size_t numCharacters = Content::getNumCharacters(currentLine);
        std::string newLine;
        size_t num = Content::getNumCharacters(event.key);
        for (size_t i = 0; i <= numCharacters; i++) {
            if (i == this->cursorPosition.getX()) {
                for (char c : event.key) {
                    newLine += c;
                }
                //i += num; if you want insert mode writing
                numCharacters += num;
            }
            newLine += Content::getCharacter(currentLine, i);
        }
        currentFileContents.changeLine(this->cursorPosition.getY(), newLine);
        for (size_t i = 0; i < num; i++) {
            this->moveCursorRight();
        }
    }
    return true;
}

void EditorWindow::tick() {
    Window::tick();
}
