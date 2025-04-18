#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <stdexcept>
using namespace std;

void bubbleSort(vector<int>& arr); 
void insertionSort(vector<int>& arr);
void selectionSort(vector<int>& arr);
void mergeSort(vector<int>& arr);
void heapSort(vector<int>& arr);
void quickSort(vector<int>& arr);
void cocktailShakerSort(vector<int>& arr);
void combSort(vector<int>& arr);
void tournament_sort(vector<int>& arr);
void introSort(vector<int>& arr);
void librarySort(vector<int>& arr);
void timSort(vector<int>& arr);


// Bubble Sort
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

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; 
    int n2 = right - mid; 

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];


    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

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

// Heap Sort
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

void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    buildMaxHeap(arr);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

// Quick Sort
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    return mid;
}

int partition(vector<int>& arr, int low, int high) {
    int pivot_index = medianOfThree(arr, low, high);
    swap(arr[pivot_index], arr[high]); // 피벗을 마지막으로 이동
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

void _quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        _quick_sort(arr, low, pi - 1);
        _quick_sort(arr, pi + 1, high);
    }
}

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

// Tournament Sort
void tournament_sort(vector<int>& arr) {
    int n = arr.size();
    if(n == 0) return;
    
    // n보다 큰 2의 제곱
    int m = 1;
    while(m < n)
        m *= 2;
    
    // root=1
    const int INF = numeric_limits<int>::max();
    vector<int> tree(2 * m, INF);
    
    // leaf node
    for (int i = 0; i < m; i++) {
        if (i < n)
            tree[m + i] = arr[i];
        else
            tree[m + i] = INF;
    }
    
    // 내부 노드 채우기기
    for (int i = m - 1; i >= 1; i--) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }
    
    for (int j = 0; j < n; j++) {
        // winner
        int winner = tree[1];
        arr[j] = winner;
        
        // winner index 내려가면서서
        int idx = 1;
        while(idx < m) {
            if (tree[2 * idx] == winner)
                idx = 2 * idx;
            else
                idx = 2 * idx + 1;
        }
        tree[idx] = INF;
        
        // 다 바꾸는 것 보다 효율적
        while(idx > 1) {
            idx /= 2;
            tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
        }
    }
}


// intro sort에서 삽입 정렬을 수행하는 함수
void _insertionSort(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// intro sort에서 maxHeapify를 수행하는 함수
void _maxHeapify(vector<int>& arr, int low, int heapSize, int i) {
    int largest = i;
    int left = 2 * (i - low) + 1 + low;   // 왼쪽 자식 인덱스
    int right = 2 * (i - low) + 2 + low;  // 오른쪽 자식 인덱스

    if (left < low + heapSize && arr[left] > arr[largest])
        largest = left;
    if (right < low + heapSize && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        _maxHeapify(arr, low, heapSize, largest);
    }
}

// intro sort에서 힙 정렬을 수행하는 함수
void _heapSort(vector<int>& arr, int low, int high) {
    int heapSize = high - low + 1;
    for (int i = low + heapSize / 2 - 1; i >= low; i--)
        _maxHeapify(arr, low, heapSize, i);

    for (int i = high; i > low; i--) {
        swap(arr[low], arr[i]);
        heapSize--;
        _maxHeapify(arr, low, heapSize, low);
    }
}

// intro sort에서 재귀적으로 호출되는 함수
void introsortUtil(vector<int>& arr, int low, int high, int max_depth) {
    // 16개 이하의 원소에 대해 삽입 정렬을 수행
    if (high - low <= 16) {
        _insertionSort(arr, low, high);
        return;
    }
    // 힙 정렬을 사용하여 깊이를 제한
    if (max_depth == 0) {
        _heapSort(arr, low, high);
        return;
    }
    // 퀵 정렬을 수행
    int pivot = partition(arr, low, high);
    introsortUtil(arr, low, pivot - 1, max_depth - 1);
    introsortUtil(arr, pivot + 1, high, max_depth - 1);
}

// introSort
void introSort(vector<int>& arr) {
    int n = arr.size();
    int max_depth = (n > 0) ? 2 * int(floor(log2(n))) : 0;
    introsortUtil(arr, 0, n - 1, max_depth);
}

const int INF = numeric_limits<int>::max();

//Library Sort
void librarySort(vector<int>& arr) {
    int n = arr.size();
    int m = 2 * n;
    vector<pair<int, int>> output(m, {INF, INF}); 
    int count = 0;

    auto find_pos = [&](int x, int idx) {
        int left = 0, right = m - 1, res = m;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (output[mid].first == INF || output[mid] > make_pair(x, idx)) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return res;
    };

    auto rebalance = [&]() {
        vector<pair<int, int>> temp(m, {INF, INF});
        int gap = 2;
        int idx = gap;
        for (auto& v : output) {
            if (v.first != INF) {
                if (idx >= m) throw runtime_error("Overflow during rebalance");
                temp[idx] = v;
                idx += gap;
            }
        }
        output = temp;
    };

    for (int i = 0; i < n; ++i) {
        int x = arr[i];
        int pos = find_pos(x, i);


        int insert_pos = pos;
        while (insert_pos < m && output[insert_pos].first != INF)
            insert_pos++;

        if (insert_pos == m) {
            rebalance();
            insert_pos = find_pos(x, i);
            while (insert_pos < m && output[insert_pos].first != INF)
                insert_pos++;
            if (insert_pos == m)
                throw runtime_error("Still no gap after rebalance");
        }

        for (int k = insert_pos; k > pos; --k)
            output[k] = output[k - 1];

        output[pos] = {x, i};
        count++;
    }

    int idx = 0;
    for (auto& v : output)
        if (v.first != INF)
            arr[idx++] = v.first;
}

int computeMinRun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}

// Galloping Mode를 적용한 Merge 함수
void gallopMerge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    const int minGallop = 7;
    while (i < L.size() && j < R.size()) {
        int count1 = 0, count2 = 0;
        while (i < L.size() && j < R.size()) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
                count1++;
                count2 = 0;
                if (count1 >= minGallop) break;
            } else {
                arr[k++] = R[j++];
                count2++;
                count1 = 0;
                if (count2 >= minGallop) break;
            }
        }
        // L 연속 
        if (i < L.size() && j < R.size() && count1 >= minGallop) {
            auto pos = upper_bound(L.begin() + i, L.end(), R[j]);
            int num = pos - (L.begin() + i);
            copy(L.begin() + i, pos, arr.begin() + k);
            k += num;
            i += num;
            continue;
        }
        // R 연속
        if (i < L.size() && j < R.size() && count2 >= minGallop) {
            auto pos = lower_bound(R.begin() + j, R.end(), L[i]);
            int num = pos - (R.begin() + j);
            copy(R.begin() + j, pos, arr.begin() + k);
            k += num;
            j += num;
            continue;
        }
    }
    while (i < L.size())
        arr[k++] = L[i++];
    while (j < R.size())
        arr[k++] = R[j++];
}

struct Run {
    int start;
    int length;
};

// Tim Sort
void timSort(vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return;
    
    int minRun = computeMinRun(n);
    vector<Run> runs;
    
    int i = 0;
    while (i < n) {
        int runStart = i;
        i++;
        if (i == n) {
            runs.push_back({runStart, 1});
            break;
        }
      
        if (arr[i - 1] <= arr[i]) { 
            while (i < n && arr[i - 1] <= arr[i])
                i++;
        } else { 
            while (i < n && arr[i - 1] > arr[i])
                i++;
            reverse(arr.begin() + runStart, arr.begin() + i);
        }
        int runLen = i - runStart;
        
        if (runLen < minRun) {
            int end = min(n, runStart + minRun);
            _insertionSort(arr, runStart, end - 1);
            runLen = end - runStart;
            i = end;
        }
        runs.push_back({runStart, runLen});
    }
    
    // run들을 반복적으로 병합
    while (runs.size() > 1) {
        vector<Run> newRuns;
        for (size_t j = 0; j < runs.size(); j += 2) {
            if (j + 1 < runs.size()) {
                int start = runs[j].start;
                int mid = runs[j].start + runs[j].length - 1;
                int end = runs[j + 1].start + runs[j + 1].length - 1;
                gallopMerge(arr, start, mid, end);
                newRuns.push_back({start, runs[j].length + runs[j + 1].length});
            } else {  
                newRuns.push_back(runs[j]);
            }
        }
        runs = move(newRuns);
    }
}