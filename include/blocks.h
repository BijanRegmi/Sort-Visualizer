#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>

class Blocks{
public:
    int amount;                 // Number of items to be sorted

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

    // Operator Overloading
    float operator[](int);
    void operator()(int, int);
};

#endif // BLOCKS_H
