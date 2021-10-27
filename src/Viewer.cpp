#include "Viewer.h"

// Constructors
Viewer::Viewer(){}

Viewer::Viewer(int w, int h, Blocks* b, Algorithms* a){
    width = w;
    height = h;
    blk = b;
    alg = a;

    // Initialize $(blk->amount) number of rectangles
    rects = std::vector<sf::RectangleShape>(blk->amount);

    // Create and set textures
    texture.create(width, height);
    this->setTexture(texture.getTexture());
}

// Renderer
void Viewer::render(){
    float r_dx = width/rects.size();                    // Width of the rectangular block
    
    texture.clear();
    for (int i=0; i<rects.size(); i++){
        float h = blk->items[i];                        //Using items instead of blk[] so that counters aren't updated

        rects[i].setSize(sf::Vector2f(r_dx, h));
        rects[i].setPosition(i*r_dx, height-h);

        texture.draw(rects[i]);
    }
    texture.display();
}
