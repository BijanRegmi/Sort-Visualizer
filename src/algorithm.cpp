#include "algorithm.h"

// Constructor
Algorithms::Algorithms(Blocks& b):data(b){
    def_delays = {b.amount, 0, 30000/data.amount, 400000/data.amount, 450000/data.amount, 500000/data.amount, 450000/data.amount, 8000/data.amount};
    setalg(0);
    working = false;
    sorted = true;
    algcount = alglist.size();

    sortingThread = std::thread(&Algorithms::algo, this);   // Setup the thread
}

// Controllers
void Algorithms::start(){
    working = true;
}

void Algorithms::stop(){
    working = false;
    sortingThread.detach();
}

// Setters
void Algorithms::setalg(int s){
    if (s == -1)
        selectedAlg = (selectedAlg + 1)%algcount;
    else if (s == -2)
        selectedAlg = (selectedAlg + algcount - 1)%algcount;
    else
        selectedAlg = s;
    data.reset_head();
    data.reset_counters();
    data.setdelay(def_delays[selectedAlg]);
}

// Data Extractors
std::string Algorithms::getalg(){
    return alglist[selectedAlg];
}

// Thread function
void Algorithms::algo(){
    while(true){
        if (!working){
            std::cout << "";        // IDK why but this needs to be here. Prolly the thread requires some task to do.
            continue;
        }

        data.reset_counters();
        data.reset_head();
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
        case 4:
            Algorithms::quicksort();
            Algorithms::check();
            break;
        case 5:
            Algorithms::radixsort();
            Algorithms::check();
            break;
        case 6:
            Algorithms::insertionsort();
            Algorithms::check();
            break;
        case 7:
            Algorithms::selectionsort();
            Algorithms::check();
            break;
        }
        working = false;
    }
}

// Sorting Algorithm Implementations
void Algorithms::check(){
    selectedAlg = 0;
    data.setdelay(def_delays[selectedAlg]);
    for (data.head.c = 0; data.head.c < data.amount-1; data.head.c++){
        float val = data.items[data.head.c];
        if (val > data.items[data.head.c+1]){
            std::cout << "ERROR at " << data.head.c << std::endl;
            break;
        }
        data.sound.play(2, 0.5+(0.5*val)/data.max_val);
        std::this_thread::sleep_for(std::chrono::microseconds(def_delays[0]));
    }
    sorted = (data.amount-1 == data.head.c) ? true : false;
    if (sorted){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        data.sound.play(3, 1);
        data.head.c = -2;           // Denotes that checking has been completed and the array is completely sorted
    } else 
        data.sound.play(4, 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::shuffle(){
    std::random_shuffle(data.items.begin(), data.items.end());
    sorted = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::bubblesort(){
    for (int i = 0; i < data.amount; i += 1){
        for (int j = 0; j < data.amount-i-1; j += 1){

            if (data.cmp(j, j+1) == 1){
                data.b_swap(j, j+1);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::mergesort(){
    m_ms(0, data.amount-1);
}
void Algorithms::m_ms(int left, int right){
    if (left>=right) return;
    int mid = (left + right)/2;

    m_ms(left, mid);
    m_ms(mid+1, right);

    m_merge(left, mid, right);
}
void Algorithms::m_merge(int left, int mid, int right){
    int left_n = mid - left + 1;
    int right_n = right - mid;      // right - (mid + 1) + 1
    
    // Temporary arrays
    int left_arr[left_n];
    int right_arr[right_n];

    // Copying arrays
    for (int i=0; i<left_n; i++) left_arr[i] = data[left+i];
    for (int i=0; i<right_n; i++) right_arr[i] = data[mid+1+i];

    // Pointing ints
    int i = 0;
    int j = 0;
    int k = 0;

    // Writing to data
    while (i<left_n && j<right_n)
    {
        if (left_arr[i] <= right_arr[j]){
            data(left+k, left_arr[i]);
            i++;
        } else {
            data(left+k, right_arr[j]);
            j++; 
        }
        k++;
    }
    while (i<left_n){
        data(left+k, left_arr[i]);
        i++; k++;
    }
    while (j<right_n){
        data(left+k, right_arr[j]);
        j++; k++;
    }
    

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::quicksort(){
    q_qs(0, data.amount-1);
}
void Algorithms::q_qs(int low, int high){
    if (low >= high) return;
    _q_pivot_index = q_fix(low, high);

    q_qs(low, _q_pivot_index-1);
    q_qs(_q_pivot_index+1, high);
}
int Algorithms::q_fix(int low, int high){
    int i = low - 1;

    for (int j = low; j<high; j++){
        if (data.cmp(j, high) == -1){
            i++;
            if (i != j) data.b_swap(i, j);
        }
    }

    data.b_swap(i+1, high);
    return i+1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::radixsort(){
    int max_val = r_max();
    for (int p=1; max_val/p>0; p*=10)
        r_cs(p);
}
void Algorithms::r_cs(int place){
    int s = data.amount;
    float output[s];
    int count[10] = {0};

    // Storing how many times a digit appeared at the $(place)th position
    for (int i=0; i<s; i++)
        count[ (static_cast<int>(data[i])/place)%10 ]++;

    // Cummulative adding
    for (int i=1; i<10; i++)
        count[i] += count[i-1];
    
    // Shifting right
    for (int i=9; i>0; i--)
        count[i] = count[i-1];
    count[0] = 0;

    // Filling output array
    for (int i=0; i<s; i++){
        float val = data[i];
        int digit = (static_cast<int>(val)/place)%10;
        output[ count[digit] ] = val;
        count[digit]++;
    }

    // Filling original array
    for (int i=0; i<s; i++){
        data(i, output[i]);
    }
}
int Algorithms::r_max(){
    int max_i = 0;
    for (int i=0; i<data.amount; i++)
        if (data.cmp(i, max_i) == 1) max_i = i;
    return data[max_i];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::insertionsort(){
    for (int i = 1; i<data.amount; i++){
        int curr = data[i];
        int j = i - 1;

        while (j>=0 && data[j] > curr){
            data(j+1, data[j]);
            j--;
        }
        data(j+1, curr);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::selectionsort(){
    int min_val_index = 0;
    for (int i=0; i<data.amount-1; ++i){
        min_val_index = i;

        // Finding the minimum value index
        for (int j=i+1; j<data.amount; ++j)
            if (data.cmp(j, min_val_index) == -1)
                min_val_index = j;
        
        if (min_val_index != i) data.b_swap(i, min_val_index);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
