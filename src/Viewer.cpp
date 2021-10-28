#include "Viewer.h"

// Constructors
Viewer::Viewer(int w, int h, Blocks& b, Algorithms& a):blk(b), alg(a){
    width = w;
    height = h;
    r_dx = width/blk.amount;

    // Initialize $(blk.amount) number of rectangles
    rects = std::vector<sf::RectangleShape>(blk.amount);

    // Create and set textures
    texture.create(width, height);
    this->setTexture(texture.getTexture());
}

// Renderer
void Viewer::render(){
    texture.clear();
    for (unsigned int i=0; i<rects.size(); i++){
        float h = blk.items[i];                        //Using items instead of blk[] so that counters aren't updated

        rects[i].setSize(sf::Vector2f(r_dx, h));
        rects[i].setPosition(i*r_dx, height-h);

        colorizer(i);

        texture.draw(rects[i]);
    }
    texture.display();
}

// Colorizer
void Viewer::colorizer(int i){
    

    if (alg.working){
        switch (alg.selectedAlg)
        {
        case 0:                                                                         // Check
            if (i <= blk.head.c+3)
                rects[i].setFillColor(sf::Color::Green);        // Green for those rects which are in sorted order
            else
                rects[i].setFillColor(sf::Color::White);
            break;
        case 1:                                                                         // Shuffle
            rects[i].setFillColor(sf::Color::White);            // All white
            break;
        case 2:                                                                         // Bubblesort   |   Coloring reading head only
            if (i == blk.head.r)
                rects[i].setFillColor(sf::Color::Red);          // Red reading head
            else
                rects[i].setFillColor(sf::Color::White);
            break;
        case 4:                                                                         // Quicksort
            if (i == alg._q_pivot_index)
                rects[i].setFillColor(sf::Color(169, 0, 255));  // Purple for the pivot element
            else if (i == blk.head.r)
                rects[i].setFillColor(sf::Color::Red);          // Red reading head
            else if (i == blk.head.w)
                rects[i].setFillColor(sf::Color::Blue);         // Blue writing head
            else
                rects[i].setFillColor(sf::Color::White);        // White none
        case 3:                                                                         // Mergesort
        case 5:                                                                         // Radixsort
            if (i == blk.head.r)
                rects[i].setFillColor(sf::Color::Red);          // Red reading head
            else if (i == blk.head.w)
                rects[i].setFillColor(sf::Color::Blue);         // Blue writing head
            else
                rects[i].setFillColor(sf::Color::White);        // White none
            break;
        default:
            break;
        }
    } else {
        if (blk.head.c == -2)                                                           // If the array is sorted and selected alg is still {check}
            rects[i].setFillColor(sf::Color::Green);            // All green
        else 
            rects[i].setFillColor(sf::Color::White);            // If no work is going on then white
    }
}