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
    if (!working){
        data.reset_counters();
        view.unmark_all();
    }
    setdesc();
}

void Algorithms::setdesc(){
    switch (selectedAlg)
    {
    case 0:
        algdesc = "Checks if the array is sorted or not. Colors green for sorted blocks and red for unsorted block.";
        break;
    case 1:
        algdesc = "Shuffles the blocks using std::random_shuffle.";
        break;
    case 2:
        algdesc = "Bubblesort O(n^2):: Reading: Red";
        break;
    case 3:
        algdesc = "Mergesort O(nlogn):: Reading: Red | Writing: Blue | Left: Cyan | Right: Yellow";
        break;
    case 4:
        algdesc = "Quicksort O(nlogn): Reading: Red | Swaping elements: Light Red | Pivot: Green";
        break;
    case 5:
        algdesc = "Radixsort O(d*(n+b)): Reading: Red | Writing: Blue | Finding Max: Yellow";
        break;
    case 6:
        algdesc = "InsertionSort O(n^2): Reading: Red | Writing: Blue";
        break;
    case 7:
        algdesc = "Selection Sort O(n^2): Writing: Blue | Finding Min: Purple";
        break;
    default:
        break;
    }
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
        view.unmark_all();
        switch(selectedAlg){
        case 0:
            Algorithms::check();
            break;
        case 1:
            Algorithms::shuffle();
            break;
        case 2:
            Algorithms::bubblesort();
            data.stopsound();
            Algorithms::check();
            break;
        case 3:
            Algorithms::mergesort();
            data.stopsound();
            Algorithms::check();
            break;
        case 4:
            Algorithms::quicksort();
            data.stopsound();
            Algorithms::check();
            break;
        case 5:
            Algorithms::radixsort();
            data.stopsound();
            Algorithms::check();
            break;
        case 6:
            Algorithms::insertionsort();
            data.stopsound();
            Algorithms::check();
            break;
        case 7:
            Algorithms::selectionsort();
            data.stopsound();
            Algorithms::check();
            break;
        }
        working = false;
    }
}

// Sorting Algorithm Implementations
void Algorithms::check(){
    selectedAlg = 0;
    setdesc();
    int n = data.amount-1, c = -1;
    
    view.mark(0, 0x00ff00ff);                               // First element is obviously in correct order
    
    for (c = 0; c < n; ++c){
        float val = data.items[c];
        if (val > data.items[c+1]){
            view.mark(c+1, 0xff0000ff);                     // Mark red for unsorted elem
            break;
        }
        data.sound.play(2, 0.5+(0.5*val)/data.max_val);
        view.mark(c+1, 0x00ff00ff);                           // Mark green for sorted element
        std::this_thread::sleep_for(std::chrono::milliseconds(2000/n));     // Whatever be the size of the data checking is completed in 2sec
    }
    sorted = (n == c) ? true : false;
    if (sorted){
        view.mark(n, 0x00ff00ff);                           // If sorted mark last element as green
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
    for (int i = 0, n = data.amount; i != n-1; ++i){
        for (int j = 0; j < n-i-1; ++j){
            view.mark(j, 0xff0000ff);               // Mark reading index
            if (data.cmp(j, j+1) == 1)
                data.b_swap(j, j+1);
            view.unmark(j);                         // Unmark reading index
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
    view.mark(left, 0x00ffffff);    // Mark left boundary
    view.mark(right, 0xffff00ff);   // Mark right boundary
    int left_n = mid - left + 1;
    int right_n = right - mid;      // right - (mid + 1) + 1
    
    // Temporary arrays
    int left_arr[left_n];
    int right_arr[right_n];

    // Copying arrays
    for (int i=0; i<left_n; ++i){
        view.mark(left+i+1, 0xff0000ff);                // Mark reading index
        left_arr[i] = data[left+i];
        view.unmark(left+i+1);                          // Unmark reading index
    }
    for (int i=0; i<right_n; ++i){
        view.mark(mid+1+i, 0xff0000ff);                 // Mark reading index
        right_arr[i] = data[mid+1+i];
        view.unmark(mid+1+i);                           // Unmark reading index
    }

    // Pointing ints
    int i = 0;
    int j = 0;
    int k = left;

    // Writing to data
    while (i<left_n && j<right_n)
    {
        view.mark(k-1, 0x0000ffff);           // Mark writing index
        if (left_arr[i] <= right_arr[j]){
            data(k, left_arr[i]);
            i++;
        } else {
            data(k, right_arr[j]);
            j++; 
        }
        view.unmark(k-1);                     // Unmark writing index
        k++;
    }
    while (i<left_n){
        view.mark(k-1, 0x0000ffff);           // Mark writing index
        data(k, left_arr[i]);
        i++;
        view.unmark(k-1);                     // Unmark writing index
        k++;
    }
    while (j<right_n){
        view.mark(k-1, 0x0000ffff);           // Mark writing index
        data(k, right_arr[j]);
        j++;
        view.unmark(k-1);                     // Unmark writing index
        k++;
    }
    view.unmark(left);                      // Unmark left boundary
    view.unmark(right);                     // Unmark right boundary
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::quicksort(){
    q_qs(0, data.amount-1);
}
void Algorithms::q_qs(int low, int high){
    int _q_pivot_index;
    if (low >= high) return;
    _q_pivot_index = q_fix(low, high);
    view.mark(_q_pivot_index, 0x00ff00ff);              // Mark pivot index as green

    q_qs(low, _q_pivot_index-1);
    q_qs(_q_pivot_index+1, high);
    view.unmark(_q_pivot_index);                        // Unmark pivot index
}
int Algorithms::q_fix(int low, int high){
    int i = low - 1;

    for (int j = low; j<high; ++j){
        view.mark(i, j-1, 0xde5f5fff);                      // Mark swaping indexes as light red
        view.mark(j-1, 0xff0000ff);                         // Mark reading index as red
        if (data.cmp(j, high) == -1){
            i++;
            if (i != j) data.b_swap(i, j);
        }
        view.unmark(i-1, j);                                // Unmark swaping indexes and reading index
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
    for (int i=0; i<s; ++i){
        view.mark(i, 0xff0000ff);                           // Mark reading index as red
        count[ (static_cast<int>(data[i])/place)%10 ]++;
        view.unmark(i);                                     // Unmark reading index
    }

    // Cummulative adding
    for (int i=1; i<10; ++i)
        count[i] += count[i-1];
    
    // Shifting right
    for (int i=9; i>0; --i)
        count[i] = count[i-1];
    count[0] = 0;

    // Filling output array
    for (int i=0; i<s; ++i){
        view.mark(i, 0xff0000ff);                       // Mark reading index as red
        float val = data[i];
        int digit = (static_cast<int>(val)/place)%10;
        output[ count[digit] ] = val;
        count[digit]++;
        view.unmark(i);                                 // Unmark reading index
    }

    // Filling original array
    for (int i=0; i<s; ++i){
        view.mark(i, 0x0000ffff);                       // Mark writing index as blue
        data(i, output[i]);
        view.unmark(i);                                 // Unmark writing index
    }
}
int Algorithms::r_max(){
    int max_i = 0;
    for (int i=0, j=data.amount; i<j; ++i){
        view.mark(i, 0xffff00ff);                       // Mark max finding index as yellow
        if (data.cmp(i, max_i) == 1) max_i = i;
        view.unmark(i);                                 // Unmark max finding index
    }
    return data[max_i];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::insertionsort(){
    for (int i = 1, k=data.amount; i<k; ++i){
        view.mark(i, 0xff0000ff);               // Mark reading index as red
        int curr = data[i];
        int j = i - 1;

        while (j>=0 && data[j] > curr){
            view.mark(j+1, 0x0000ffff);         // Mark writing index as blue
            data(j+1, data[j]);
            view.unmark(j+1);                   // Unmark writing index
            j--;
        }
        data(j+1, curr);
        view.unmark(i);                         // Unmark reading index
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::selectionsort(){
    int min_val_index = 0;
    for (int i=0, n=data.amount; i<n; ++i){
        min_val_index = i;

        // Finding the minimum value index
        for (int j=i+1; j<n; ++j){
            view.mark(j, 0x411e59ff);                   // Mark min finding index as purple
            if (data.cmp(j, min_val_index) == -1)
                min_val_index = j;
            view.unmark(j);                             // Unmark min finding index
        }
        
        if (min_val_index != i){
            view.mark(i, 0x0000ffff);                   // Mark writing index as red
            data.b_swap(i, min_val_index);
            view.unmark(i);                             // Mark writing index
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
