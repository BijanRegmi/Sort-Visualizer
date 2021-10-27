#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>

class Blocks{
public:
    int amount;                 // Number of items to be sorted

    // Counters
    int comparecounter;
    int readcounter;
    int swapcounter;

    std::vector<int> items;     // Array of items

    int r_head;                 // Reading head
    int c_head;                 // Checking head

    // Constructors
    Blocks();
    Blocks(int width, int height);

    // Data utils
    int cmp(int, int);
    void b_swap(int, int);
    void reset_counters();

    // Operator Overloading
    float operator[](int);
};

#endif // BLOCKS_H
