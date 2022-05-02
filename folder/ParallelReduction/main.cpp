#include <iostream>
#include <vector>
#include <thread>
#include "parallel_sum_omp1.h"
#include "parallel_sum.h"
#include <chrono>
#include <iostream>
#include "built_in_OMP.h"
using namespace std::chrono;



int main() {
    auto start = high_resolution_clock::now();
    runOMP(100, 100);
    auto stop = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    runRegular(100, 100);
    auto stop2 = high_resolution_clock::now();

    auto start3 = high_resolution_clock::now();
    runBI(100, 100);
    auto stop3 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    auto duration3 = duration_cast<microseconds>(stop3 - start3);


    std::cout << "results of threaded sum: " << duration.count() << "\n";
    std::cout << "results of OMP sum: " << duration2.count() << "\n";
    std::cout << "results of reduction sum: " << duration3.count() << "\n";

}


