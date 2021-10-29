#include "Viewer.h"

// Constructors
Viewer::Viewer(int w, int h, Blocks& b):blk(b){
    width = w;
    height = h;
    r_dx = (float)width/blk.amount;

    // Initialize $(blk.amount) number of rectangles
    rects = std::vector<sf::RectangleShape>(blk.amount);

    // Empty the tracking lists
    cleartracking();

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

        updatetrackvalues();
        colorizer(i);

        texture.draw(rects[i]);
    }
    texture.display();
}

void Viewer::add_to_track(int& w, int s, uint32_t c){
    tracklist.push_back( std::pair<int&, int>(w, c) );
    trackvalues.push_back(std::list<int>(s, -1));
}

void Viewer::updatetrackvalues(){
    int n = tracklist.size();

    for (int i=0; i<n; i++){
        int val = tracklist[i].first;       // Current value
        int pval = trackvalues[i].back();   // Previous value
        if (pval != val){                   // Don't update if value hasn't changed
            trackvalues[i].push_back(val);
            trackvalues[i].pop_front();
        }
    }
}

void Viewer::cleartracking(){
    tracklist.clear();
    trackvalues.clear();
}

// Colorizer
void Viewer::colorizer(int index){
    int n = tracklist.size();

    for (int i=0; i<n; i++){
        for (auto x: trackvalues[i]){
            if(x == index){
                rects[index].setFillColor(sf::Color(tracklist[i].second));
                return;
            }
        }
    }
    rects[index].setFillColor(sf::Color::White);
}