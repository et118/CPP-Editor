//
// Created by et118 on 10/01/2026.
//
#include "../../include/Util/StringUtils.h"

//https://en.wikipedia.org/wiki/ANSI_escape_code?lang=en

std::string StringUtils::to_standard(std::string string) {
    //Bold
    string = replace_all(string, "\x1B[1m", "");
    string = replace_all(string, "\x1B[22m", "");
    //Underline
    string = replace_all(string, "\x1B[4m", "");
    string = replace_all(string, "\x1B[24m", "");
    //Italics
    string = replace_all(string, "\x1B[3m", "");
    string = replace_all(string, "\x1B[23m", "");
    //Strikethrough
    string = replace_all(string, "\x1B[9m", "");
    string = replace_all(string, "\x1B[29m", "");
    //Inverted
    string = replace_all(string, "\x1B[7m", "");
    string = replace_all(string, "\x1B[27m", "");

    return string;
}

std::string StringUtils::to_bold(const std::string &string) {
    return "\x1B[1m" + string + "\x1B[22m";
}

std::string StringUtils::to_underline(const std::string &string) {
    return "\x1B[4m" + string + "\x1B[24m";
}

std::string StringUtils::to_italics(const std::string &string) {
    return "\x1B[3m" + string + "\x1B[23m";
}

std::string StringUtils::to_strikethrough(const std::string &string) {
    return "\x1B[9m" + string + "\x1B[29m";
}

std::string StringUtils::to_inverted(const std::string &string) {
    return "\x1B[7m" + string + "\x1B[27m";
}

std::string StringUtils::get_all_ansi_terminators() {
    return  std::string("\x1B[22m") + "\x1B[24m" + "\x1B[23m" + "\x1B[29m" + "\x1B[27m";
}

//https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
std::string StringUtils::replace_all(std::string string, const std::string& target, const std::string& replacement) {
    size_t start = 0;
    while((start = string.find(target, start)) != std::string::npos) {
        string.replace(start, target.length(), replacement);
        start += replacement.length();
    }
    return string;
}


