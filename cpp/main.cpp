#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>
#include <filesystem>
#include "sorts.h"
#include "sortT.h"
using namespace std;
using namespace std::chrono;

// 입력 생성
vector<int> generate_input(int size, const string& type) {
    vector<int> base(size);
    iota(base.begin(), base.end(), 0);
    if (type == "reversed") {
        reverse(base.begin(), base.end());
    } else if (type == "random") {
        shuffle(base.begin(), base.end(), mt19937{random_device{}()});
    } else if (type == "partially") {
        int mid = size / 2;
        shuffle(base.begin() + mid, base.end(), mt19937{random_device{}()});
    }
    return base;
}

// 정렬 정확도 확인
bool is_sorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

vector<pair<int, int>> generate_stable_input_pair(int size) {
    vector<pair<int,int>> base(size);
    for (int i = 0; i < size; i++) {
        base[i] = {i % 2, 0};
    }
    shuffle(base.begin(), base.end(), mt19937{random_device{}()});
    for (int i = 0; i < size; i++) {
        base[i].second = i;
    }
    return base;
}

bool isStable(const vector<pair<int,int>>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i-1].first == arr[i].first && arr[i-1].second > arr[i].second)
            return false;
    }
    return true;
}

bool test_stability(const string& name) {
    vector<pair<int, int>> stable_data = generate_stable_input_pair(5000);
    if (name == "Bubble Sort") bubbleSortT(stable_data);
    else if (name == "Insertion Sort") insertionSortT(stable_data);
    else if (name == "Selection Sort") selectionSortT(stable_data);
    else if (name == "Merge Sort") mergeSortT(stable_data);
    else if (name == "Heap Sort") heapSortT(stable_data);
    else if (name == "Quick Sort") quickSortT(stable_data);
    else if (name == "Cocktail Shaker Sort") cocktailShakerSortT(stable_data);
    else if (name == "Comb Sort") combSortT(stable_data);
    else if (name == "Tournament Sort") tournament_sortT(stable_data);
    else if (name == "Intro Sort") introSortT(stable_data);
    else if (name == "Library Sort") librarySortT(stable_data);
    else if (name == "Tim Sort") timSortT(stable_data);
    return isStable(stable_data);
}


// 메인 함수
int main() {
    filesystem::create_directories("./results");

    vector<pair<string, void(*)(vector<int>&)>> algorithms = {
        {"Bubble Sort", bubbleSort},
        {"Insertion Sort", insertionSort},
        {"Selection Sort", selectionSort},
        {"Merge Sort", mergeSort},
        {"Heap Sort", heapSort},
        {"Quick Sort", quickSort}, 
        {"Cocktail Shaker Sort", cocktailShakerSort},
        {"Comb Sort", combSort},
        {"Tournament Sort", tournament_sort},
        {"Intro Sort", introSort},
        {"Library Sort", librarySort},
        {"Tim Sort", timSort},
    };

    vector<int> sizes = {1000, 10000, 100000, 1000000};
    vector<string> types = {"sorted", "reversed", "random", "partially"};

    for (const auto& [name, sort_fn] : algorithms) {
        string filename = "./results/" + name;
        replace(filename.begin(), filename.end(), ' ', '_');
        filename += "_results.csv";

        ofstream outfile(filename);
        outfile << "algorithm,input_type,size,avg_time,stable,correct\n";

        for (int size : sizes) {
            for (const auto& type : types) {
                vector<double> times;
                bool correct = true;
                for (int i = 0; i < 10; ++i) {
                    vector<int> data = generate_input(size, type);
                    auto expected = data;
                    sort(expected.begin(), expected.end());

                    auto test = data;
                    auto start = high_resolution_clock::now();
                    sort_fn(test);
                    auto end = high_resolution_clock::now(); 
                    duration<double> elapsed = end - start;

                    times.push_back(elapsed.count());
                    if (test != expected) correct = false;
    
                    // 만약 첫 실행 시 60초 초과면 반복 중단.
                    if (i == 0 && elapsed.count() > 60.0) {
                        cout << "Skipping remaining runs for " << name << " | size: " << size 
                             << ", type: " << type << " (took " << elapsed.count() << "s)\n";
                        break;
                    } 
                }
                double avg = accumulate(times.begin(), times.end(), 0.0) / times.size();
                bool stable = false;
                stable = test_stability(name);

                cout << name << ", " << type << ", " << size << ", " << avg 
                     << " sec, " << (stable ? "true" : "false") 
                     << ", " << (correct ? "true" : "false") << "\n";
                outfile << name << "," << type << "," << size << "," << avg << ","
                        << (stable ? "true" : "false") << "," << (correct ? "true" : "false") << "\n";
            }
        }
        outfile.close();
    }

    return 0;
}
