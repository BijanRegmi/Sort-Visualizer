#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "blocks.h"

#include <thread>
#include <chrono>
#include <algorithm>

#include <iostream>
#include <string>

class Algorithms{
private:
    Blocks* data;               // Pointer to array of data to sort

    std::thread sortingThread;  // Thread for sorting the blocks

    int algcount;               // Total number of algs in alglist

    void algo();                // Function that keeps running in the thread

    // Sorting algorithms
    void check();
    void shuffle();
    void bubblesort();
    void mergesort();   void m_ms(int left, int right);    void m_merge(int left, int mid, int right);
    void quicksort();   void q_qs(int, int);    int q_fix(int, int);

    // Algorithm list
    const std::vector<std::string> alglist = {"Check", "Shuffle", "Bubblesort", "Mergesort", "Quicksort"};
public:
    // Constructor
    Algorithms(Blocks* b);

    // Controllers
    void start();
    void stop();

    bool working;               // Set true when the algo is performing task
    bool sorted;

    unsigned int selectedAlg;   // Currently selected algorithm index from alglist

    int delay;                  // delay in microseconds

    // Setters
    void setdelay(int);         // Set delay for algorithm loops
    void setalg(int);           // Set Algorithm to use

    // Getters
    std::string getalg();       // Get currently selected alg name
};

#endif // ALGORITHM_H
