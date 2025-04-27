#ifndef COLOR_H
#define COLOR_H

#include <vector>

struct Color {
    unsigned char r, g, b;
};

std::vector<std::vector<Color>> sequentialBlur(const std::vector<std::vector<Color>>& img);
std::vector<std::vector<Color>> parallelBlurThreads(const std::vector<std::vector<Color>>& img, int num_threads);

#endif // COLOR_H