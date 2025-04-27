#ifndef COLOR_H
#define COLOR_H

#include <vector>

struct Color {
    unsigned char r, g, b;
};

std::vector<std::vector<Color>> parallelBlurOMP(const std::vector<std::vector<Color>>& img);

#endif // COLOR_H