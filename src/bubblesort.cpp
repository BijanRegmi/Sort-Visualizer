#include "sorts.h"

class bubblesort: public Sort{
private:
    int i=0, j=0;
public:
    bubblesort(int width, int height, int amount): Sort(width, height, amount){}

    void algorithm(){
        if (i<lines.size()-1){
            if (j<lines.size()-1-i){
                sf::Vector2f y1 = lines[j].getSize();
                sf::Vector2f y2 = lines[j+1].getSize();
                if (y1.y > y2.y){
                    //Swap
                    lines[j].setSize(y2);
                    lines[j+1].setSize(y1);
                }
                j++;
            } else {
                i++;
                j = 0;
            }
        }
    }
};
