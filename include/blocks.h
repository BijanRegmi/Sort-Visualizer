#ifndef BLOCKS_H
#define BLOCKS_H

#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

#include "sound_effect.h"

class Blocks{
public:
    int amount;                 // Number of items to be sorted
    int max_val;
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
        int r;                      // Reading head
        int c;                      // Checking head
        int w;                      // Writing head
    }head;
    
    std::vector<int> items;         // Array of items
    
    sound_effect& sound;            // Speaker
    
    // Constructors
    Blocks(int amount, int max_val, sound_effect& sound_obj);

    // Data utils
    int cmp(int left, int right);
    void b_swap(int a, int b);

    // Setters
    void reset_counters();
    void reset_head();
    void setdelay(int delay_time);  // Set delay for reads and writes

    // Operator Overloading
    float operator[](int);
    void operator()(int, int);
};

#endif // BLOCKS_H
