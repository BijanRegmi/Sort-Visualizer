#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>

class Blocks{
private:
    int amount;

    // Counters
    int comparecounter;
    int readcounter;
    int swapcounter;

public:
    std::vector<int> items;

    // Constructors
    Blocks();
    Blocks(int, int);

    // Data utils
    int cmp(int, int);
    void b_swap(int, int);

    // Operator Overloading
    float operator[](int);

    // Data Extractors
    int getSize();
    int compcount();
    int readcount();
    int swapcount();
};

#endif // BLOCKS_H
