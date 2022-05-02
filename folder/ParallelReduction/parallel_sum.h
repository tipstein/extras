//
// Created by Adam Weinstein on 4/25/22.
//

#ifndef PARALLELREDUCTION_PARALLEL_SUM_H
#define PARALLELREDUCTION_PARALLEL_SUM_H

#include <iostream>
#include <vector>
#include <thread>
#include <math.h>
#define PI 3.14159265

static int array_position;
static int globalTotal;
static std::vector<int>addList;

static void pushIt(int runningTotal) {
    { // Begins a new (sub) scope
        std::mutex door; //mutex declaration
        std::unique_lock<std::mutex> my_lock(door); //lock door
        addList.push_back(runningTotal);
    }
}

static void nibble(int arr[], int locationToStart, int chunkSize) {

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
    pushIt(runningTotal);

}

static int run_threads(int arr[], size_t num_threads, int itemsPerThread) {
    //crate i number of threads
    for (int i = 0; i < num_threads; ++i) {
        //send each thread to nibble at array
        std::thread consumer(nibble, arr, array_position, itemsPerThread);
        //increment global variable by number of items per thread
        array_position += itemsPerThread;
        consumer.join();
    }
    int returnVal = 0;
    for(int c : addList) {
        returnVal += c;
    }
    return returnVal;
}

static int addItUp(int arr[], size_t arraySize, size_t num_threads) {
    //divide
    int itemsPerthread = (int) arraySize/num_threads;

//    std::cout << "items per thread: " << itemsPerthread << "\n";

    int total = run_threads(arr, num_threads, itemsPerthread);
//    std::cout << "total is: " << total << "\n";

    return total;
}

static void runRegular(size_t size, size_t threadCount) {
    int count = 0;
    array_position = 0;
    //size of array
   size = size;
    int arr[size];

    //add elements to array
    for (int i = 0; i < size; ++i) {
        arr[i] = i+1;
        count ++;
    }
//    std::cout << "size is " << count << "\n";
    int checkTotal = 0;
    for (int i = 0; i < size; ++i) {
        checkTotal += arr[i];
    }
//    std::cout << "value to check against: " << checkTotal << "\n";
    //number of threads
   threadCount =5;

    //pass: array, size of array, number of threads
    addItUp(arr, size, threadCount);
}


#endif //PARALLELREDUCTION_PARALLEL_SUM_H
