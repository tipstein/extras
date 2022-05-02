cmake_minimum_required(VERSION 3.21)
project(ParallelReduction)

set(CMAKE_CXX_STANDARD 14)

add_executable(ParallelReduction main.cpp parallel_sum_omp1.cpp built_in_OMP.h omp.h)
