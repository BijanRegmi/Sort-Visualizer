#include "sorts.h"

class bubblesort: public Sort{
private:
    int i=0, j=0;
    bool isSorting=false;
public:
    bubblesort(int width, int height, int amount): Sort(width, height, amount){}

    void algorithm(){
        for (int i=0; i<lines.size(); i++){
            for (int j=0; j<lines.size()-i-1; j++){
                sf::Vector2f y1 = lines[j].getSize();
                sf::Vector2f y2 = lines[j+1].getSize();

                std::this_thread::sleep_for(std::chrono::milliseconds(2));

                if (y1.y > y2.y){
                    //Swap
                    lines[j].setSize(y2);
                    lines[j+1].setSize(y1);
                }
            }
        }
    }

    void start(){
        if (!isSorting){
            sortingThread = std::thread(&bubblesort::algorithm, this);
            isSorting = true;
        }
    }
};
