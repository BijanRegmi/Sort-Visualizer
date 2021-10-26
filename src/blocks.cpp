#include "blocks.h"

// Constructors
Blocks::Blocks(){}

Blocks::Blocks(int a, int m){
    amount = a;

    readcounter = 0;
    comparecounter = 0;

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

// Operators
float Blocks::operator[](int i){

    if (i < amount){
        readcounter++;
        return items[i];
    }
}

// Data Extractors
int Blocks::getSize(){
    return amount;
}

int Blocks::compcount(){
    return comparecounter;
}

int Blocks::readcount(){
    return readcounter;
}

int Blocks::swapcount(){
    return swapcounter;
}
