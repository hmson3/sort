# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

# 프로젝트 정보
project(
  SORTING
  VERSION 0.1
  DESCRIPTION "sorting algorithms"
  LANGUAGES CXX)

add_executable (main main.cpp)
target_compile_options(main PUBLIC -Wall -Werror)

add_executable (median median_of_k.cpp)
target_compile_options(median PUBLIC -Wall -Werror)
