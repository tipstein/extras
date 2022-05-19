//
// Created by Ben Powell on 4/25/22.
//

#ifndef PARALLELREDUCTION_BUILT_IN_OMP_H
#define PARALLELREDUCTION_BUILT_IN_OMP_H
#include <iostream>
#include <vector>
#include <thread>
#include <math.h>
#define PI 3.14159265
#include "omp.h"

static int array_positionBI;
static int globalTotalBI;
static std::vector<int>addListBI;

static void pushItBI(int runningTotal) {
    { // Begins a new (sub) scope

        addListBI.push_back(runningTotal);
    }
}

static int nibbleBI(int arr[], int locationToStart, int chunkSize) {

    //total kept track by each thread
    int runningTotal = 0;

    //for loop size begins at locationToStart and increments to the chunkSize
    for (int i = locationToStart; i < locationToStart+chunkSize; ++i) {
        int temp = arr[i] + 56789;
        for (int j = 0; j < 100000; ++j) {
            temp = sin(temp* PI /180) + cos(temp* PI /180) + tan(temp* PI /180);
        }

        runningTotal += (int)temp;
    }
    //thread pushes individual total


    pushItBI(runningTotal);
    return runningTotal;

}

static int run_threadsBI(int arr[], size_t num_threads, int itemsPerThread) {
    //crate i number of threads
    int sum = 0;
    omp_set_num_threads(5);


    omp_lock_t writelock;
    omp_init_lock(&writelock);
#pragma omp parallel for
    for (int i = 0; i < itemsPerThread; ++i)
    {
        omp_set_lock(&writelock);
        sum += nibbleBI( arr, array_positionBI, itemsPerThread);
        omp_unset_lock(&writelock);
    }
    omp_destroy_lock(&writelock);

    std::cout << "results of parallel reduction: " << sum;
    int returnVal = 0;
    for(int c : addListBI) {
        returnVal += c;
    }
    return returnVal;
}

static void addItUpBI(int arr[], size_t arraySize, size_t num_threads) {
    //divide
    int itemsPerthread = (int) arraySize/num_threads;

//    std::cout << "items per thread: " << itemsPerthread << "\n";

   run_threadsBI(arr, num_threads, itemsPerthread);
//    std::cout << "total is: " << total << "\n";


}

static int runBI(size_t size, size_t threadCount) {
    int count = 0;
    array_positionBI = 0;
    //size of array
    size = size;
    int arr[size];

    //add elements to array
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
        count++;
    }
//    std::cout << "size is " << count << "\n";
    int checkTotal = 0;
    for (int i = 0; i < size; ++i) {
        checkTotal += arr[i];
    }
//    std::cout << "value to check against: " << checkTotal << "\n";
    //number of threads
    threadCount = 5;

    //pass: array, size of array, number of threads
    int total = addItUp(arr, size, threadCount);


}

#endif //PARALLELREDUCTION_BUILT_IN_OMP_H
