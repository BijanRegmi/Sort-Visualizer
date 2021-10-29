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
    for (int i=0; i<rects.size(); i++){
        float h = blk.items[i];                        //Using items instead of blk[] so that counters aren't updated

        rects[i].setSize(sf::Vector2f(r_dx, h));
        rects[i].setPosition(i*r_dx, height-h);

        updatetrackvalues();
        colorizer(i);

        texture.draw(rects[i]);
    }
    texture.display();
}

void Viewer::add_to_track(volatile int* w, int s, uint32_t c){
    tracklist.push_back(std::pair<volatile int*, uint32_t>(w, c));
    trackvalues.push_back(std::vector<int>(s, -1));
    checkvalues();
}

void Viewer::checkvalues(){
    int n = tracklist.size();

    for (int i=0; i<n; i++){
        std::cout << "tracklist[" << i << "]->first: " << tracklist[i].first << std::endl
                  << "tracklist[" << i << "]->second: " << tracklist[i].second << std::endl;
        int n2 = trackvalues[i].size();
        for (int j = 0; j<n2; j++){
                std::cout << "trackvalues[" << i << "][" << j << "]: " << trackvalues[i][j] << std::endl << std::endl;
        }
    }
}

void Viewer::updatetrackvalues(){
    int n = tracklist.size();

    for (int i=0; i<n; i++){
        int val = *(tracklist[i].first);       // Current value
        int pval = *(trackvalues[i].end());   // Previous value
        if (pval != val){                   // Update only if value has changed
            int n2 = trackvalues[i].size();
            for (int j = n2-1; j>0; j--){
                trackvalues[i][j-1] = trackvalues[i][j];
            }
            trackvalues[i][n2-1] = val;
        }
    }
}

void Viewer::cleartracking(){
    trackvalues.clear();
    tracklist.clear();
}

// Colorizer
void Viewer::colorizer(int index){
    int n = tracklist.size();
    int a = blk.amount;

    for (int i=0; i<n; i++){
        int n2 = trackvalues[i].size();
        for (int j=0; j<n2; j++){
            int x = trackvalues[i][j];
            if ( x < 0 || x > a) continue;
            else if(x == index){
                rects[index].setFillColor(sf::Color(tracklist[i].second));
                return;
            }
        }
    }
    rects[index].setFillColor(sf::Color::White);
}