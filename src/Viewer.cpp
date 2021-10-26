#include "Viewer.h"

// Constructors
Viewer::Viewer(){}

Viewer::Viewer(int w, int h, Blocks* b){
    width = w;
    height = h;
    blk = b;

    texture.create(width, height);
    this->setTexture(texture.getTexture());
}

// Renderer
void Viewer::render(){
    float r_dx = width/blk->getSize();

    texture.clear();
    for (int i=0; i<blk->getSize(); i++){
        float h = blk->items[i];                        //Using items instead of blk[] so that counters aren't updated

        sf::RectangleShape rect(sf::Vector2f(r_dx, h));
        rect.setPosition(i*r_dx, height-h);

        texture.draw(rect);
    }
    texture.display();
}
