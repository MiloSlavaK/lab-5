#include "color.h"
#include <iostream>
#include <chrono>
#include <thread> 

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

    // Sequential
    auto start_seq = std::chrono::high_resolution_clock::now();
    auto blurred_seq = sequentialBlur(image);
    auto end_seq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seq = end_seq - start_seq;
    std::cout << "Sequential blur time: " << elapsed_seq.count() << " s\n";

    // Parallel
    int num_threads = std::thread::hardware_concurrency();
    std::cout << "\nUsing " << num_threads << " threads\n";

    auto start_par = std::chrono::high_resolution_clock::now();
    auto blurred_par = parallelBlurThreads(image, num_threads);
    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_par = end_par - start_par;
    std::cout << "Parallel blur time: " << elapsed_par.count() << " s\n";

    std::cout << "\nSpeedup: " << elapsed_seq.count() / elapsed_par.count() << "x\n";

    return 0;
}