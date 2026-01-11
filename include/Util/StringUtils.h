//
// Created by et118 on 10/01/2026.
//

#ifndef CPP_EDITOR_STRINGUTILS_H
#define CPP_EDITOR_STRINGUTILS_H
#include <string>
namespace StringUtils {
    std::string to_standard(std::string string);
    std::string to_bold(const std::string& string);
    std::string to_underline(const std::string& string);
    std::string to_italics(const std::string& string);
    std::string to_strikethrough(const std::string& string);
    std::string to_inverted(const std::string& string);
    // TODO add colors

    std::string get_all_ansi_terminators();

    std::string replace_all(std::string string, const std::string& target, const std::string& replacement);
}
#endif //CPP_EDITOR_STRINGUTILS_H