#ifndef BLOCKS_H
#define BLOCKS_H

#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

class Blocks{
public:
    int amount;                 // Number of items to be sorted
    int r_delay;                // delay in microseconds
    int w_delay;                // delay in microseconds

    struct COUNTERS
    {
        int c;                  // Compare counter
        int r;                  // Read counter
        int w;                  // Write counter
        int s;                  // Swap counter
    }counter;
    
    struct HEADS
    {
        int r;                  // Reading head
        int c;                  // Checking head
        int w;                  // Writing head
    }head;
    
    std::vector<int> items;     // Array of items
    
    // Constructors
    Blocks();
    Blocks(int width, int height);

    // Data utils
    int cmp(int, int);
    void b_swap(int, int);
    void reset_counters();
    void reset_head();
    void setdelay(int);         // Set delay for reads and writes

    // Operator Overloading
    float operator[](int);
    void operator()(int, int);
};

#endif // BLOCKS_H
