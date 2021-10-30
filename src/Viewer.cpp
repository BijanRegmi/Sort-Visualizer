#include "Viewer.h"

// Constructors
Viewer::Viewer(int w, int h, Blocks& b):blk(b){
    width = w;
    height = h;
    r_dx = (float)width/blk.amount;

    // Initialize $(blk.amount) number of rectangles
    rects = std::vector<sf::RectangleShape>(blk.amount);

    cols = std::vector<sf::Color>(blk.amount, sf::Color::White);

    // Create and set textures
    texture.create(width, height);
    this->setTexture(texture.getTexture());
}

// Renderer
void Viewer::render(){
    texture.clear();
    for (int i=0, j=rects.size(); i<j; ++i){
        float h = blk.items[i];                        //Using items instead of blk[] so that counters aren't updated

        rects[i].setSize(sf::Vector2f(r_dx, h));
        rects[i].setPosition(i*r_dx, height-h);
        rects[i].setFillColor(cols[i]);
        texture.draw(rects[i]);
    }
    texture.display();
}

// Marker
void Viewer::mark(int i, uint32_t c){
    if (i>=rects.size()) return;
    cols[i] = sf::Color(c);
}

void Viewer::mark(int s, int e, uint32_t c){
    std::fill(cols.begin()+s, cols.begin()+e, sf::Color(c));
}

void Viewer::unmark(int i){
    if (i>=rects.size()) return;
    cols[i] = sf::Color::White;
}

void Viewer::unmark(int s, int e){
    std::fill(cols.begin()+s, cols.begin()+e, sf::Color::White);
}

void Viewer::unmark_all(){
    std::fill(cols.begin(), cols.end(), sf::Color::White);
}

// Colorizer
void Viewer::colorizer(int index){
    rects[index].setFillColor(sf::Color::White);
}