#include "algorithm.h"

// Constructor
Algorithms::Algorithms(Blocks* b):data(b){
    selectedAlg = 0;
    working = false;
    sorted = true;
    algcount = alglist.size();

    setdelay(20);

    sortingThread = std::thread(&Algorithms::algo, this);   // Setup the thread
}

// Thread function
void Algorithms::algo(){
    while(true){
        if (!working){
            std::cout << "";        // IDK why but this needs to be here. Prolly the thread requires some task to do.
            continue;
        }

        data->reset_counters();
        switch(selectedAlg){
        case 0:
            Algorithms::check();
            break;
        case 1:
            Algorithms::shuffle();
            break;
        case 2:
            Algorithms::bubblesort();
            Algorithms::check();
            break;
        case 3:
            Algorithms::mergesort();
            Algorithms::check();
            break;
        }
        working = false;
    }
}

// Controllers
void Algorithms::start(){
    working = true;
}

void Algorithms::stop(){
    working = false;
    sortingThread.detach();
}

void Algorithms::setalg(int s){
    if (s == -1)
        selectedAlg = (selectedAlg + 1)%algcount;
    else if (s == -2)
        selectedAlg = (selectedAlg - 1)%algcount;
    else
        selectedAlg = s;
}

void Algorithms::setdelay(int d){
    if (d > 0)
        delay = d;
    else if (d == -1)
        delay += 10;
    else if (d == -2 && delay > 10)
        delay -= 10;
    else if (d == -3)
        delay += 100;
    else if (d == -4 && delay > 100)
        delay -=100;
    else if (d == -5)
        delay += 1000;
    else if (d == -6 && delay > 1000)
        delay -= 1000;
}

// Data Extractors
std::string Algorithms::getalg(){
    return alglist[selectedAlg];
}

// Sorting Algorithms
void Algorithms::check(){
    for (data->c_head = 0; data->c_head < data->amount-1; data->c_head++){
        if (data->cmp(data->c_head, data->c_head+1) != -1){
            std::cout << "ERROR at " << data->c_head << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(delay));
    }
    sorted = (data->amount-1 == data->c_head) ? true : false;
}

void Algorithms::shuffle(){
    std::random_shuffle(data->items.begin(), data->items.end());
    sorted = false;
}

void Algorithms::bubblesort(){
    for (int i = 0; i < data->amount; i += 1){
        for (int j = 0; j < data->amount-i-1; j += 1){

            if (data->cmp(j, j+1) == 1){
                data->b_swap(j, j+1);
            }

            std::this_thread::sleep_for(std::chrono::microseconds(delay));
        }
    }
}

void Algorithms::mergesort(){
    std::cout << "Not implemented" << std::endl;
}
