#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

int main() {
    int counter = 0;
    std::mutex mtx;
    const int NUM_THREADS = 10;
    const int ITERATIONS = 1000000;

    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    // Создаем и запускаем потоки
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back([&] {
            for (int j = 0; j < ITERATIONS; ++j) {
                std::lock_guard<std::mutex> lock(mtx);
                counter++;
            }
            });
    }

    // Ждем завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Result: " << counter << std::endl;
    std::cout << "Time: " << duration.count() << " ms" << std::endl;

    return 0;
}

