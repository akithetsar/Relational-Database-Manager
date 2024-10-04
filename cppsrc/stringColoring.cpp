//
// Created by akith on 5/10/2024.
//
#include "stringColoring.h"
std::string colorString(const std::string &string, int colorId) {
    switch (colorId) {
        case COLOR_GREEN:
            return "\033[32m" + string + "\033[0m";  // Green
        case COLOR_BLUE:
            return "\033[34m" + string + "\033[0m";  // Blue
        case COLOR_PURPLE:
            return "\033[35m" + string + "\033[0m"; // Purple
        case COLOR_YELLOW:
            return "\033[33m" + string + "\033[0m"; // Yellow
        case COLOR_RED:
            return "\033[31m" + string + "\033[0m";  // Red
        default:
            return string;  // Return the original string if colorId is invalid
    }
}
