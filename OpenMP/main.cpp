#include "color.h"
#include <iostream>
#include <chrono>

int main() {
    const int size = 2000;
    std::vector<std::vector<Color>> image(size, std::vector<Color>(size));


    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            image[y][x] = {
                static_cast<unsigned char>((x + y) % 256),
                static_cast<unsigned char>(x % 256),
                static_cast<unsigned char>(y % 256)
            };
        }
    }


    // Параллельное размытие (OpenMP)
    auto start_par = std::chrono::high_resolution_clock::now();
    auto blurred_par = parallelBlurOMP(image);
    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_par = end_par - start_par;
    std::cout << "Parallel blur time (OMP): " << elapsed_par.count() << " s\n";


    return 0;
}