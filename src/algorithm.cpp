#include "algorithm.h"

// Constructor
Algorithms::Algorithms(Blocks& b, Viewer& v):data(b), view(v){
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
    data.reset_counters();
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
        switch(selectedAlg){
        case 0:
            //Algorithms::check();
            break;
        case 1:
            Algorithms::shuffle();
            break;
        case 2:
            Algorithms::bubblesort();
            //Algorithms::check();
            break;
        case 3:
            Algorithms::mergesort();
            //Algorithms::check();
            break;
        case 4:
            Algorithms::quicksort();
            //Algorithms::check();
            break;
        case 5:
            Algorithms::radixsort();
            //Algorithms::check();
            break;
        case 6:
            Algorithms::insertionsort();
            //Algorithms::check();
            break;
        case 7:
            Algorithms::selectionsort();
            //Algorithms::check();
            break;
        }
        view.cleartracking();
        working = false;
    }
}

// Sorting Algorithm Implementations
void Algorithms::check(){
    selectedAlg = 0;
    
    int n = data.amount;

    //int delay = data.amount * 50;

    int c = -1;
    view.add_to_track(c, 1, 0x00ff00ff);

    for (c = 0; c < n-1; c++){
        float val = data.items[c];
        if (val > data.items[c+1]){
            std::cout << "ERROR at " << c << std::endl;
            break;
        }
        data.sound.play(2, 0.5+(0.5*val)/data.max_val);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    sorted = (n-1 == c) ? true : false;
    if (sorted){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        data.sound.play(3, 1);
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
    int i = -1;
    int j = -1;
    view.add_to_track(j, 3, 0xff0000ff);
    //std::cout << "Sent data are: j, 3, 0xff0000ff " << 0xff0000ff;

    int n = data.amount;
    int cnt = 0;
    // Core
    for (i = 0; i < n; i++){
        for (j = 0; j < n-i-1; j++){
            if (data.cmp(j, j+1) == 1)
                data.b_swap(j, j+1);
            std::cout << "Iterator " << cnt << ": " << std::endl;
            view.checkvalues();
            cnt++;
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
    
    view.add_to_track(left, 1, 0x00ff00ff);
    view.add_to_track(right, 1, 0x0000ffff);

    // Temporary arrays
    int left_arr[left_n];
    int right_arr[right_n];

    // Copying arrays
    for (int i=0; i<left_n; i++) left_arr[i] = data[left+i];
    for (int i=0; i<right_n; i++) right_arr[i] = data[mid+1+i];

    // Pointing ints
    int i = 0;
    int j = 0;
    int k = left;

    view.add_to_track(k, 1, 0xff0000ff);

    // Writing to data
    while (i<left_n && j<right_n)
    {
        if (left_arr[i] <= right_arr[j]){
            data(k, left_arr[i]);
            i++;
        } else {
            data(k, right_arr[j]);
            j++; 
        }
        view.checkvalues();
        k++;
    }
    while (i<left_n){
        data(k, left_arr[i]);
        i++; k++;
        view.checkvalues();
    }
    while (j<right_n){
        data(k, right_arr[j]);
        j++; k++;
        view.checkvalues();
    }
    
    view.cleartracking();    

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
