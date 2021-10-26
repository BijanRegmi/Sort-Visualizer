#include "algorithm.h"

// Constructor
Algorithms::Algorithms(Blocks* b):data(b){
    selectedAlg = 0;
    isSorting = false;
    sortingThread = std::thread(&Algorithms::algo, this);   // Setup the thread
}

// Thread function
void Algorithms::algo(){
    while(true){
        if (!isSorting){
            std::cout << "";        // IDK why but this needs to be here. Prolly the thread requires some task to do.
            continue;
        }

        switch(selectedAlg){
        case 0:
            Algorithms::shuffle();
            break;
        case 1:
            Algorithms::bubblesort();
            break;
        case 2:
            Algorithms::mergesort();
            break;
        }
        isSorting = false;
    }
}

// Controllers
void Algorithms::start(){
    isSorting = true;
}

void Algorithms::stop(){
    isSorting = false;
    sortingThread.detach();
}

void Algorithms::setalg(int s){
    selectedAlg = s;
}

// Sorting Algorithms
void Algorithms::shuffle(){
    std::random_shuffle(data->items.begin(), data->items.end());
}

void Algorithms::bubblesort(){
    for (int i = 0; i < data->getSize(); i += 1){
        for (int j = 0; j < data->getSize()-i-1; j += 1){

            if (data->cmp(j, j+1) == 1){
                data->b_swap(j, j+1);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
}

void Algorithms::mergesort(){
    std::cout << "Not implemented" << std::endl;
}
