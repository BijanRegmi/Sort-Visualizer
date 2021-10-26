#include "Viewer.h"

// Constructors
Viewer::Viewer(){}

Viewer::Viewer(int w, int h, Blocks* b){
    width = w;
    height = h;
    blk = b;

    // Create and set textures
    texture.create(width, height);
    this->setTexture(texture.getTexture());
}

// Renderer
void Viewer::render(){
    float r_dx = width/blk->amount;                     // Width of the rectangular block
    int r_head = blk->r_head;                          // Reader head position
    int c_head = blk->c_head;                          // Checker head position

    texture.clear();
    for (int i=0; i<blk->amount; i++){
        float h = blk->items[i];                        //Using items instead of blk[] so that counters aren't updated

        sf::RectangleShape rect(sf::Vector2f(r_dx, h));
        rect.setPosition(i*r_dx, height-h);

        // Highlight the currently reading block
        if (c_head >= i && c_head > 0)
            rect.setFillColor(sf::Color::Green);
        else if (i == r_head)
            rect.setFillColor(sf::Color::Red);

        texture.draw(rect);
    }
    texture.display();
}
