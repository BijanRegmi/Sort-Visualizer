#include "blocks.h"

// Constructors
Blocks::Blocks(){}

Blocks::Blocks(int a, int m){
    amount = a;

    reset_counters();
    reset_head();

    items.clear();
    for (int i=1; i<=amount; i++){
        items.push_back(i*m/a);
    }
}

// Data utils
int Blocks::cmp(int i, int j){

    counter.c++;                                // Update compare counter

    int a = this->operator[](i);                // this used instead of items so as to increase the read counter
    int b = this->operator[](j);

    if (a == b)
        return 0;
    else if (a < b)
        return -1;
    else
        return 1;
}

void Blocks::b_swap(int i, int j){

    counter.s++;                                // Update swap counter

    int t = this->operator[](i);                // this used instead of items so as to increase the read counter
    this->operator()(i, this->operator[](j));   // to increase the write counter
    this->operator()(j, t);
}

void Blocks::reset_counters(){
    counter.c = 0;
    counter.r = 0;
    counter.w = 0;
    counter.s = 0;
}

void Blocks::reset_head(){
    head.c = -1;
    head.r = -1;
    head.w = -1;
}

// Operators
float Blocks::operator[](int i){                // Read
    head.r = i;                                 // Update reading head
    counter.r++;                                // Update read counter
    return items[i];
}

void Blocks::operator()(int dest, int val){     // Write
    head.w = dest;                              // Update writing head
    counter.w++;                                // Update write counter
    items[dest] = val;
}
