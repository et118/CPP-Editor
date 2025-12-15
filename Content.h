//
// Created by et118 on 12/2/25.
//

#ifndef SKETCH3_CONTENT_H
#define SKETCH3_CONTENT_H
#include <string>
#include <vector>

class Content {
private:
    std::vector<std::string> lines;
public:
    void addLine(const std::string &line);
    size_t getNumLines() const;
    std::string getLine(size_t index);

    Content& operator+=(Content& other);
};
#endif //SKETCH3_CONTENT_H