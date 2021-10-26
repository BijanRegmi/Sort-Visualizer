#include "blocks.h"

// Constructors
Blocks::Blocks(){}

Blocks::Blocks(int a, int m){
    amount = a;

    reset_counters();

    items.clear();
    for (int i=1; i<=amount; i++){
        items.push_back(i*m/a);
    }
}

// Data utils
int Blocks::cmp(int i, int j){

    comparecounter++;

    int a = (*this)[i];             //this used instead of items so as to increase the read counter
    int b = (*this)[j];

    if (a == b)
        return 0;
    else if (a < b)
        return -1;
    else
        return 1;
}

void Blocks::b_swap(int i, int j){

    swapcounter++;

    int t = (*this)[i];
    items[i] = (*this)[j];
    items[j] = t;
}

void Blocks::reset_counters(){
    comparecounter = 0;
    readcounter = 0;
    swapcounter = 0;
    c_head = -1;
    r_head = -1;
}

// Operators
float Blocks::operator[](int i){

    if (i < amount){
        r_head = i;
        readcounter++;
        return items[i];
    }
}
