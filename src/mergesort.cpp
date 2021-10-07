#include "sorts.h"

class mergesort: public Sort{
private:
    int i=0, j=0;
    bool isSorting=false;
public:
    mergesort(int width, int height, int amount): Sort(width, height, amount){}

    void algorithm(){
        mergeSort(0, lines.size()-1);
    }

    void merge(int l, int m, int r) {
       int i, j, k, nl, nr;
       nl = m-l+1;
       nr = r-m;

       sf::Vector2f larr[nl], rarr[nr];

       for(i = 0; i<nl; i++)
          larr[i] = lines[l+i].getSize();

       for(j = 0; j<nr; j++)
          rarr[j] = lines[m+1+j].getSize();

       i = 0; j = 0; k = l;

       while(i < nl && j<nr) {
          if(larr[i].y <= rarr[j].y) {
             lines[k].setSize(larr[i]);
             i++;
          }else{
             lines[k].setSize(rarr[j]);
             j++;
          }
          k++;
       }

       while(i<nl) {
          lines[k].setSize(larr[i]);
          i++; k++;
       }

       while(j<nr) {
          lines[k].setSize(rarr[j]);
          j++; k++;
       }

       std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    void mergeSort(int l, int r) {
       int m;
       if(l < r) {
          int m = l+(r-l)/2;
          mergeSort(l, m);
          mergeSort(m+1, r);
          merge(l, m, r);
       }
    }

    void start(){
        if (!isSorting){
            sortingThread = std::thread(&mergesort::algorithm, this);
            isSorting = true;
        }
    }
};
