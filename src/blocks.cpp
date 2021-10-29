#include "blocks.h"

// Constructors
Blocks::Blocks(int a, int m, sound_effect& s):sound(s){
    amount = a;
    max_val = m;

    setdelay(10);
    reset_counters();

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

// Setters
void Blocks::reset_counters(){
    counter.c = 0;
    counter.r = 0;
    counter.w = 0;
    counter.s = 0;
}

void Blocks::setdelay(int d){
    if (d >= 0){
        r_delay = d;
        w_delay = d;
    } else if (d == -1)                     // +
        r_delay += 10;
    else if (d == -2 && r_delay >= 10)      // -
        r_delay -= 10;
    else if (d == -3)                       // S+
        w_delay += 10;
    else if (d == -4 && w_delay >= 10)      // S-
        w_delay -=10;
    else if (d == -5)                       // C+
        r_delay += 100;
    else if (d == -6 && r_delay >= 100)     // C-
        r_delay -= 100;
    else if (d == -7)                       // CS+
        w_delay += 100;
    else if (d == -8 && w_delay >= 100)     // CS-
        w_delay -= 100;
}

// Operators
float Blocks::operator[](int i){                                        // Read
    if (i>=amount){
        std::cout << "Out of bound value " << i << " selected!";
        return 0;
    }
    counter.r++;                                                        // Update read counter
    float val = items[i];
    sound.play(0, 0.2+0.8*val/max_val);                                 // Play reading sound   |   Mapping val to [0.2, 1]
    std::this_thread::sleep_for(std::chrono::microseconds(r_delay));    // Pause for read delay
    return val;
}

void Blocks::operator()(int dest, int val){                             // Write
    if (dest>=amount){
        std::cout << "Out of bound value " << dest << " selected!";
        return;
    }
    counter.w++;                                                        // Update write counter
    sound.play(1, 1+val/max_val);                                       // Play writing sound   |   Mapping val to [1, 2]
    std::this_thread::sleep_for(std::chrono::microseconds(w_delay));    // Pause for write delay
    items[dest] = val;
}
