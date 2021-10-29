#include "Viewer.h"

// Constructors
Viewer::Viewer(int w, int h, Blocks& b, Algorithms& a):blk(b), alg(a){
    width = w;
    height = h;
    r_dx = (float)width/blk.amount;

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

        updatewatchvalues();
        colorizer();

        texture.draw(rects[i]);
    }
    texture.display();
}

void Viewer::add_to_track(int& w, int s){
    watchlist.push_back( std::pair<int&, int>(w, s) );
    watch_values.push_back(std::list<int>(s, -1));
}

void Viewer::updatewatchvalues(){
    int n = watchlist.size();

    for (int i=0; i<n; i++){
        watch_values[i].push_back(watchlist[i].first);
        watch_values[i].pop_front();
    }
}

void Viewer::clear_track_list(){
    watchlist.clear();
}

// Colorizer
void Viewer::colorizer(){
    
}