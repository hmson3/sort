# Sorting Algorithms Analysis

This repository provides a collection of classic and modern sorting algorithms implemented in C++.  
Additionally, this project includes an experimental analysis of the median-of-k pivot selection strategy for Quick Sort.

## Sorting Algorithms Implemented (in `sorts.h`)

- Bubble Sort
- Insertion Sort
- Selection Sort
- Merge Sort
- Heap Sort
- Quick Sort (Median-of-Three optimized)
- Comb Sort
- Cocktail Shaker Sort
- Tournament Sort
- Intro Sort
- Library Sort
- Tim Sort

## Experiment Description (main.cpp)

- Input Types: sorted / reversed / random / partially sorted
- Input Sizes: 1,000 ~ 1,000,000
- Each test repeated up to 10 times
- If 1st run exceeds 1 minute → skip remaining runs
- Correctness checked automatically
- Outputs results to: `results/{algorithm_name}_results.csv`

## Median-of-k Experiment (median_of_k.cpp)

- Try different k values for Quick Sort pivot (3, 5, 7, ...)
- Measure execution time by input size
- Output result to `median_of_k_result.csv`
- Goal: Find optimal k for best performance
