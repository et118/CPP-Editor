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
public:
    void addLine(const std::string& line);
    size_t getNumLines() const;
    std::string getLine(size_t index);
};
#endif //CPP_EDITOR_CONTENT_H