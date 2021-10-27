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
        case 0:
            if (i <= blk.head.c+1)
                rects[i].setFillColor(sf::Color::Green);
            else
                rects[i].setFillColor(sf::Color::White);
            break;
        case 2:
            if (i == blk.head.r)
                rects[i].setFillColor(sf::Color::Red);
            else
                rects[i].setFillColor(sf::Color::White);
            break;
        case 4:
        case 5:
            if (i == blk.head.r)
                rects[i].setFillColor(sf::Color::Red);
            else if (i == blk.head.w)
                rects[i].setFillColor(sf::Color::Blue);
            else
                rects[i].setFillColor(sf::Color::White);
            break;
        default:
            break;
        }
    } else {
        if (blk.head.c == -1)
            rects[i].setFillColor(sf::Color::White);
    }
}