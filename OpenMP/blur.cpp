#include "color.h"
#include <omp.h>
#include <vector>


std::vector<std::vector<Color>> parallelBlurOMP(const std::vector<std::vector<Color>>& img) {
    if (img.empty()) return {};

    const size_t h = img.size();
    const size_t w = img[0].size();
    std::vector<std::vector<Color>> result(h, std::vector<Color>(w));

#pragma omp parallel for
    for (int y = 0; y < static_cast<int>(h); y++) {
        for (size_t x = 0; x < w; x++) {
            int sum_r = 0, sum_g = 0, sum_b = 0;
            int count = 0;

            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    const int nx = static_cast<int>(x) + dx;
                    const int ny = y + dy;

                    if (nx >= 0 && nx < static_cast<int>(w) && ny >= 0 && ny < static_cast<int>(h)) {
                        sum_r += img[ny][nx].r;
                        sum_g += img[ny][nx].g;
                        sum_b += img[ny][nx].b;
                        count++;
                    }
                }
            }

            result[y][x] = {
                static_cast<unsigned char>(sum_r / count),
                static_cast<unsigned char>(sum_g / count),
                static_cast<unsigned char>(sum_b / count)
            };
        }
    }

    return result;
}