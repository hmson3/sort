#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>
#include <filesystem>
#include "sorts.h"


// 입력 생성
std::vector<int> generate_input(int size, const std::string& type) {
    std::vector<int> base(size);
    std::iota(base.begin(), base.end(), 0);
    if (type == "reversed") {
        std::reverse(base.begin(), base.end());
    } else if (type == "random") {
        std::shuffle(base.begin(), base.end(), std::mt19937{std::random_device{}()});
    } else if (type == "partially") {
        int mid = size / 2;
        std::shuffle(base.begin() + mid, base.end(), std::mt19937{std::random_device{}()});
    }
    return base;
}

// 정렬 정확도 확인
bool is_sorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

// 메인 함수
int main() {
    using namespace std::chrono;
    std::filesystem::create_directories("../results");

    std::vector<std::pair<std::string, void(*)(std::vector<int>&)>> algorithms = {
        {"Bubble Sort", bubbleSort},
        {"Insertion Sort", insertionSort},
        {"Selection Sort", selectionSort},
        {"Merge Sort", mergeSort},
        {"Heap Sort", heapSort},
        {"Quick Sort", quickSort},
        {"Cocktail Shaker Sort", cocktailShakerSort},
        {"Comb Sort", combSort},
    };

    std::vector<int> sizes = {1000,};
    std::vector<std::string> types = {"sorted", "reversed", "random", "partially"};

    for (const auto& [name, sort_fn] : algorithms) {
        std::string filename = "../results/" + name;
        std::replace(filename.begin(), filename.end(), ' ', '_');
        filename += "_results.csv";

        std::ofstream outfile(filename);
        outfile << "algorithm,input_type,size,avg_time,correct\n";

        for (int size : sizes) {
            for (const auto& type : types) {
                std::vector<double> times;
                bool correct = true;
                for (int i = 0; i < 10; ++i) {
                    std::vector<int> data = generate_input(size, type);
                    auto expected = data;
                    std::sort(expected.begin(), expected.end());

                    auto test = data;
                    auto start = high_resolution_clock::now();
                    sort_fn(test);
                    auto end = high_resolution_clock::now();
                    duration<double> elapsed = end - start;

                    times.push_back(elapsed.count());
                    if (test != expected) correct = false;

                    if (i == 0 && elapsed.count() > 60.0) {
                        std::cout << "⚠️ Skipping remaining runs for " << name << " | size: " << size << ", type: " << type << " (took " << elapsed.count() << "s)\n";
                        break;
                    }
                }
                double avg = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
                std::cout << name << ", " << type << ", " << size << ", " << avg << " sec, " << (correct ? "true" : "false") << "\n";
                outfile << name << "," << type << "," << size << "," << avg << "," << (correct ? "true" : "false") << "\n";
            }
        }
        outfile.close();
    }

    return 0;
}
