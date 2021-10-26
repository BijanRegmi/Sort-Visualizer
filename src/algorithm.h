#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../blocks.h"

#include <thread>
#include <chrono>
#include <algorithm>

#include <iostream>

class Algorithms{
private:
    Blocks* data;               // Pointer to array of data to sort
    bool isSorting;             // Set true when the algo is performing sorting
    int selectedAlg;            // [0, bubblesort] [1, mergesort]

    std::thread sortingThread;  // Thread for sorting the blocks

    void algo();                // Function that keeps running in the thread

    // Sorting algorithms
    void shuffle();
    void bubblesort();
    void mergesort();
public:
    // Constructor
    Algorithms(Blocks* b);

    // Controllers
    void start();
    void stop();
    void setalg(int);           // Set Algorithm to use

};

#endif // ALGORITHM_H
