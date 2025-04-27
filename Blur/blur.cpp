#include "color.h"
#include <thread>
#include <execution>
#include <vector>


std::vector<std::vector<Color>> sequentialBlur(const std::vector<std::vector<Color>>& img) {
    if (img.empty()) return {};

    const size_t h = img.size();
    const size_t w = img[0].size();
    std::vector<std::vector<Color>> result(h, std::vector<Color>(w));

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            int sum_r = 0, sum_g = 0, sum_b = 0;
            int count = 0;

            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    const int nx = static_cast<int>(x) + dx;
                    const int ny = static_cast<int>(y) + dy;

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

std::vector<std::vector<Color>> parallelBlurThreads(const std::vector<std::vector<Color>>& img, int num_threads) {
    if (img.empty()) return {};

    const size_t h = img.size();
    const size_t w = img[0].size();
    std::vector<std::vector<Color>> result(h, std::vector<Color>(w));
    std::vector<std::thread> threads;

    auto blur_part = [&](size_t start_y, size_t end_y) {
        for (size_t y = start_y; y < end_y; y++) {
            for (size_t x = 0; x < w; x++) {
                int sum_r = 0, sum_g = 0, sum_b = 0;
                int count = 0;

                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        const int nx = static_cast<int>(x) + dx;
                        const int ny = static_cast<int>(y) + dy;

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
        };

    const size_t strip_height = h / num_threads;
    const size_t remaining = h % num_threads;
    size_t start_y = 0;

    for (int i = 0; i < num_threads; i++) {
        const size_t end_y = start_y + strip_height + (i < static_cast<int>(remaining) ? 1 : 0);
        threads.emplace_back(blur_part, start_y, end_y);
        start_y = end_y;
    }

    for (auto& t : threads) {
        t.join();
    }

    return result;
}