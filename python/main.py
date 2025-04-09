import random
import time
import copy
import csv
from collections import defaultdict
from tqdm import tqdm
import os
from sorts import bubble_sort, insertion_sort, selection_sort, merge_sort, heap_sort, quick_sort, tim_sort, cocktail_shaker_sort, comb_sort, library_sort, tournament_sort, intro_sort   # 정렬 함수 분리

output_dir = "python/results"
os.makedirs(output_dir, exist_ok=True)

# 정렬 알고리즘 목록
algorithms = {
    'Bubble Sort' : bubble_sort,
    'Insertion Sort' : insertion_sort,
    'Selection Sort' : selection_sort,
    #ok'Merge Sort' : merge_sort,
    #ok'Heap Sort' : heap_sort,
    #ok 'Quick Sort' : quick_sort,

    #ok 'Tim Sort' : tim_sort,
    'Cocktail Shaker Sort' : cocktail_shaker_sort,
    'Comb Sort' : comb_sort,
    # 'Library Sort' : library_sort,
    #ok 'Tournament Sort' : tournament_sort,
    #ok 'Intro Sort' : intro_sort,
}

# 입력 크기 및 유형
input_sizes = [1000]
input_types = ['sorted', 'reversed', 'random', 'partially']

# 입력 생성 함수
def generate_input(size, kind):
    base = list(range(size))
    if kind == 'sorted':
        return base
    elif kind == 'reversed':
        return base[::-1]
    elif kind == 'random':
        random.shuffle(base)
        return base
    elif kind == 'partially':
        part = size // 2
        half_sorted = base[:part]
        half_random = base[part:]
        random.shuffle(half_random)
        return half_sorted + half_random

# 정렬 시간 측정
def measure_time(sort_fn, data):
    start = time.perf_counter()
    sort_fn(data)
    end = time.perf_counter()
    return end - start

# 정렬 정확도 검사
def is_sorted(arr):
    return all(arr[i] <= arr[i+1] for i in range(len(arr) - 1))

# 결과 저장용 리스트
results = []

# tqdm을 이용한 진행률 표시
total_tests = len(algorithms) * len(input_sizes) * len(input_types) * 10
progress_bar = tqdm(total=total_tests, desc="Running Experiments")

for alg_name, alg_fn in algorithms.items():
    for size in input_sizes:
        for itype in input_types:
            times = []
            correct = True

            for run in range(10):
                progress_bar.set_postfix({
                    "Algorithm": alg_name,
                    "Size": size,
                    "Type": itype,
                    "Run": run + 1
                })
                progress_bar.update(1)

                data = generate_input(size, itype)
                expected = sorted(data)
                test_data = copy.deepcopy(data)

                t = measure_time(alg_fn, test_data)
                times.append(t)

                if test_data != expected:
                    correct = False

                # ⛔ 1회 실행 결과가 1분 초과되면 반복 중단
                if run == 0 and t > 60:
                    progress_bar.update(9)
                    print(f"⚠️ Skipping remaining runs for {alg_name} | size: {size}, type: {itype} (took {t:.2f}s)")
                    break

            avg_time = sum(times) / len(times)
            results.append({
                'algorithm': alg_name,
                'input_type': itype,
                'size': size,
                'avg_time': round(avg_time, 6),
                'correct': correct
            })

progress_bar.close()

# 알고리즘별로 결과 분리하여 저장
results_by_algorithm = defaultdict(list)
for result in results:
    results_by_algorithm[result['algorithm']].append(result)

for alg, records in results_by_algorithm.items():
    filename = os.path.join(output_dir, f"{alg.lower().replace(' ', '_')}_results.csv")
    with open(filename, mode='w', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=records[0].keys())
        writer.writeheader()
        writer.writerows(records)
    print(f"✅ {alg} 결과 저장 완료: {filename}")