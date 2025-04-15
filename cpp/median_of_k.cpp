#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>
#include <filesystem>
#include <chrono>
using namespace std;
using namespace chrono;

void generateInput(vector<int>& arr, int type) {
    int n = arr.size();
    if (type == 0) {  // sorted
        iota(arr.begin(), arr.end(), 1);
    }
    else if (type == 1) {  // reversed
        iota(arr.begin(), arr.end(), 1);
        reverse(arr.begin(), arr.end());
    }
    else if (type == 2) {  // random
        iota(arr.begin(), arr.end(), 1);
        random_shuffle(arr.begin(), arr.end());
    }
    else if (type == 3) {  // partial sorted
        iota(arr.begin(), arr.end(), 1);
        random_shuffle(arr.begin(), arr.begin() + n / 2);
    }
}

int medianOfK(vector<int>& arr, int low, int high, int k) {
    int size = high - low + 1;
    int gap = max(1, size / (k-1));
    vector<int> sample;
    for (int i = 0; i < k; i++) {
        sample.push_back(arr[min(low + i * gap, high)]);
    }
    sort(sample.begin(), sample.end());
    int pivotValue = sample[k / 2];
    for (int i = low; i <= high; i++) {
        if (arr[i] == pivotValue)
            return i;
    }
    return low;
}

int partition(vector<int>& arr, int low, int high, int k) {
    int pivotIndex = medianOfK(arr, low, high, k);
    swap(arr[pivotIndex], arr[high]);
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

void quickSort(vector<int>& arr, int low, int high, int k) {
    if (low < high) {
        int pi = partition(arr, low, high, k);
        quickSort(arr, low, pi - 1, k);
        quickSort(arr, pi + 1, high, k);
    }
}

int main() {
    vector<int> ns = {100, 1000, 10000, 100000, 1000000};
    vector<int> ks = {3, 5, 7, 9, 11, 13, 15, 17, 19, 21};
    vector<string> types = {"sorted", "reversed", "random", "partial"};

    ofstream fout("median_of_k_result.csv");
    fout << "n,k,input_type,time\n";

    for (int n : ns) {
        for (int k : ks) {
            for (int t = 0; t < 4; t++) {
                double total_time = 0;
                for (int trial = 0; trial < 10; trial++) {
                    vector<int> arr(n);
                    generateInput(arr, t);

                    auto start = high_resolution_clock::now();
                    quickSort(arr, 0, n - 1, k);
                    auto end = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(end - start);

                    total_time += duration.count() / 1000000.0;
                }
                fout << n << "," << k << "," << types[t] << "," << total_time / 10.0 << "\n";
            }
        }
    }
    fout.close();
}