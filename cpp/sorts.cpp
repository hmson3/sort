#include <vector>
#include "sorts.h"

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// 두 부분 배열을 병합하는 함수: arr[left..mid]와 arr[mid+1..right]를 병합
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // 왼쪽 배열 크기
    int n2 = right - mid;    // 오른쪽 배열 크기

    // 임시 배열 생성
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    // 두 임시 배열을 병합하여 arr에 저장
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    // 남은 원소 복사
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// 재귀적으로 Merge Sort를 수행하는 함수 (subarray arr[left..right] 정렬)
void merge_Sort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_Sort(arr, left, mid);       // 왼쪽 부분 정렬
        merge_Sort(arr, mid + 1, right);    // 오른쪽 부분 정렬
        merge(arr, left, mid, right);      // 두 정렬된 부분 병합
    }
}

void mergeSort(vector<int>& arr) {
    if (arr.empty())
        return;
    merge_Sort(arr, 0, arr.size() - 1);
}

// maxHeapify
void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;            // 루트
    int left = 2 * i + 1;         // 왼쪽 자식
    int right = 2 * i + 2;        // 오른쪽 자식

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// buildMaxHeap
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// heapSort
void heapSort(vector<int>& arr) {
    int n = arr.size();
    buildMaxHeap(arr);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}


int median_of_three(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int a = arr[low], b = arr[mid], c = arr[high];
    if (a > b) {
        if (b > c)
            return mid;
        else if (a > c)
            return high;
        else
            return low;
    } else {
        if (a > c)
            return low;
        else if (b > c)
            return high;
        else
            return mid;
    }
}

// partition: pivot을 기준으로 배열을 분할 (Lomuto partition)
int partition(vector<int>& arr, int low, int high) {
    int pivot_index = median_of_three(arr, low, high);
    swap(arr[pivot_index], arr[high]);  // pivot을 마지막 요소로 이동
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

// 재귀적으로 quick sort를 수행하는 함수
void _quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        _quick_sort(arr, low, pi - 1);
        _quick_sort(arr, pi + 1, high);
    }
}

// quick_sort: 전체 배열에 대해 _quick_sort를 호출하는 래퍼 함수
void quickSort(vector<int>& arr) {
    if (arr.empty()) return;
    _quick_sort(arr, 0, arr.size() - 1);
}



// Cocktail Shaker Sort
void cocktailShakerSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    int start = 0, end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        --end;
        for (int i = end; i > start; --i) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

// Comb Sort
void combSort(vector<int>& arr) {
    int n = arr.size();
    int gap = n;
    const double shrink = 1.3;
    bool sorted = false;

    while (!sorted) {
        gap = int(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = true;
        }
        for (int i = 0; i + gap < n; ++i) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                sorted = false;
            }
        }
    }
}
