//
// Created by et118 on 12/17/25.
//

#ifndef CPP_EDITOR_CONTENT_H
#define CPP_EDITOR_CONTENT_H
#include <vector>
#include <string>
class Content {
private:
    std::vector<std::string> lines;
    std::vector<size_t> lineWidths; //Caching linewidth
public:
    void addLine(const std::string& line);
    void removeLine(size_t index);
    void changeLine(size_t index, const std::string& newLine);
    size_t getNumLines() const;
    size_t getLineWidth(size_t index) const;
    std::string getLine(size_t index) const;

    static size_t widthOfLine(const std::string& line);
    static size_t getNumCharacters(const std::string &line);
    static std::string getCharacter(std::string line, size_t index);
};
#endif //CPP_EDITOR_CONTENT_H