# sorts.py

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break

def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def selection_sort(arr):
    n = len(arr)
    for i in range(n-1):
        min = i
        for j in range(i+1,n):
            if arr[j] < arr[min]:
                min = j
        arr[i], arr[min] = arr[min], arr[i]

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr)//2
        L = arr[:mid]
        R = arr[mid:]
        merge_sort(L)
        merge_sort(R)

        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
        arr[k:] = L[i:] + R[j:]

# 의사코드에서는 첫번째 인덱스가 1이지만 여기서는 0으로 설정
def max_heapify(arr, n, i):
    largest = i
    left = 2 * i + 1  # 왼쪽 자식
    right = 2 * i + 2  # 오른쪽 자식

    if left < n and arr[left] > arr[largest]:
        largest = left
    if right < n and arr[right] > arr[largest]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        max_heapify(arr, n, largest)

def build_max_heap(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        max_heapify(arr, n, i)

def heap_sort(arr):
    n = len(arr)
    build_max_heap(arr)
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]  
        max_heapify(arr, i, 0)

def quick_sort(arr):
    def _quick_sort(arr, low, high):
        if low < high:
            pi = _partition(arr, low, high)
            _quick_sort(arr, low, pi - 1)
            _quick_sort(arr, pi + 1, high)

    def median_of_three(arr, low, high):
        mid = (low + high) // 2
        a, b, c = arr[low], arr[mid], arr[high]
        if a > b:
            if b > c:
                return mid
            elif a > c:
                return high
            else:
                return low
        else:
            if a > c:
                return low
            elif b > c:
                return high
            else:
                return mid

    def _partition(arr, low, high):
        pivot_index = median_of_three(arr, low, high)
        arr[pivot_index], arr[high] = arr[high], arr[pivot_index]
        pivot = arr[high]
        i = low
        for j in range(low, high):
            if arr[j] < pivot:
                arr[i], arr[j] = arr[j], arr[i]
                i += 1
        arr[i], arr[high] = arr[high], arr[i]
        return i

    _quick_sort(arr, 0, len(arr) - 1)

MIN_RUN = 32

def merge(arr, l, m, r):
    left = arr[l:m + 1]
    right = arr[m + 1:r + 1]

    i = j = 0
    k = l

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1

    while i < len(left):
        arr[k] = left[i]
        i += 1
        k += 1

    while j < len(right):
        arr[k] = right[j]
        j += 1
        k += 1


def insertionsort(arr, left, right):
    for i in range(left + 1, right + 1):
        key = arr[i]
        j = i - 1
        while j >= left and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def tim_sort(arr):
    n = len(arr)

    # Step 1: Sort small runs with Insertion Sort
    for start in range(0, n, MIN_RUN):
        end = min(start + MIN_RUN - 1, n - 1)
        insertionsort(arr, start, end)

    # Step 2: Merge runs with Merge Sort
    size = MIN_RUN
    while size < n:
        for left in range(0, n, 2 * size):
            mid = min(n - 1, left + size - 1)
            right = min((left + 2 * size - 1), (n - 1))

            if mid < right:
                merge(arr, left, mid, right)

        size *= 2

def cocktail_shaker_sort(arr):
    n = len(arr)
    start = 0
    end = n - 1
    swapped = True

    while swapped:
        swapped = False
        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True

        if not swapped:
            break
        swapped = False
        end -= 1

        for i in range(end, start, -1):
            if arr[i - 1] > arr[i]:
                arr[i], arr[i - 1] = arr[i - 1], arr[i]
                swapped = True
        start += 1


def comb_sort(arr):
    n = len(arr)
    gap = n
    shrink = 1.3
    sorted_ = False

    while not sorted_:
        gap = int(gap // shrink)
        if gap <= 1:
            gap = 1
            sorted_ = True

        i = 0
        while i + gap < n:
            if arr[i] > arr[i + gap]:
                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                sorted_ = False
            i += 1



import bisect

def library_sort(arr):
    n = len(arr)
    size = 2 * n
    output = [None] * size
    gaps = [False] * size

    inserted = 0
    for val in arr:
        if inserted == 0:
            mid = size // 2
            output[mid] = val
            gaps[mid] = True
        else:
            present = [output[i] for i in range(size) if gaps[i]]
            idx = bisect.bisect_left(present, val)

            # 실제 삽입할 위치 탐색
            actual_index = 0
            seen = 0
            while seen < idx:
                if gaps[actual_index]:
                    seen += 1
                actual_index += 1
            while actual_index < size and gaps[actual_index]:
                actual_index += 1

            if actual_index >= size:
                raise Exception("Gap overflow — not enough space")

            output[actual_index] = val
            gaps[actual_index] = True

        inserted += 1

    # 정렬된 결과 추출
    sorted_arr = [x for x in output if x is not None]
    for i in range(n):
        arr[i] = sorted_arr[i]


def tournament_sort(arr):
    n = len(arr)
    m = 1
    while m < n:
        m *= 2
    tree = [None] * (2 * m)
    
    for i in range(m):
        if i < n:
            tree[m + i] = arr[i]
        else:
            tree[m + i] = float('inf')
    
    for i in range(m - 1, 0, -1):
        tree[i] = min(tree[2 * i], tree[2 * i + 1])
    
    for j in range(n): 
        winner = tree[1]
        arr[j] = winner  

        idx = 1  
        while idx < m:
            if tree[2 * idx] == winner:
                idx = 2 * idx
            else:
                idx = 2 * idx + 1
        
        tree[idx] = float('inf')

        while idx > 1:
            idx //= 2
            tree[idx] = min(tree[2 * idx], tree[2 * idx + 1])

import math

def heapify(arr, n, i, offset):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[offset + left] > arr[offset + largest]:
        largest = left
    
    if right < n and arr[offset + right] > arr[offset + largest]:
        largest = right
    
    if largest != i:
        arr[offset + i], arr[offset + largest] = arr[offset + largest], arr[offset + i]
        heapify(arr, n, largest, offset)

def heapsort(arr, low, high):
    n = high - low + 1
    offset = low
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i, offset)
    for i in range(n - 1, 0, -1):
        arr[low], arr[low + i] = arr[low + i], arr[low]
        heapify(arr, i, 0, offset)


def partition(arr, low, high):
    pivot = arr[high]
    i = low
    for j in range(low, high):
        if arr[j] < pivot:
            arr[i], arr[j] = arr[j], arr[i]
            i += 1
    arr[i], arr[high] = arr[high], arr[i]
    return i

def introsort_util(arr, low, high, max_depth):
    if high - low <= 16:
        insertionsort(arr, low, high)
    elif max_depth == 0:
        heapsort(arr, low, high)
    else:
        pivot = partition(arr, low, high)
        introsort_util(arr, low, pivot - 1, max_depth - 1)
        introsort_util(arr, pivot + 1, high, max_depth - 1)

def intro_sort(arr):
    n = len(arr)
    max_depth = 2 * math.floor(math.log2(n)) if n > 0 else 0
    introsort_util(arr, 0, n - 1, max_depth)