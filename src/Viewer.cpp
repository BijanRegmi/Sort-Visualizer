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
    
    std::deque< volatile int*> a(s);
    for (; s!=0; s--){
        volatile int* *iptr = new volatile int*;
        a.push_back(*iptr);
    }
    
    trackvalues.push_back(a);
}

void Viewer::checkvalues(){
    int n = tracklist.size();

    for (int i=0; i<n; i++){
        std::cout << "tracklist[" << i << "]->first: " << tracklist[i].first << std::endl
                  << "tracklist[" << i << "]->second: " << tracklist[i].second << std::endl;
        /*int n2 = trackvalues[i].size();
        for (int j = 0; j<n2; j++){
                std::cout << "trackvalues[" << i << "][" << j << "]: " << trackvalues[i][j] << std::endl << std::endl;
        }*/
    }
}

void Viewer::updatetrackvalues(){
    int n = tracklist.size();

    for (int i=0; i<n; i++){
        volatile int* val = tracklist[i].first;       // Current value
        if (trackvalues[i].back() == 0) continue;
        int pval = *(trackvalues[i].back());   // Previous value
        if (pval != *val){                   // Update only if value has changed
            delete trackvalues[i].front();
            trackvalues[i].pop_front();
            trackvalues[i].push_back(val);
        }
    }
}

void Viewer::cleartracking(){
    for (int i=0, j=trackvalues.size(); i!=j; ++i){
        for (int k=0, l=trackvalues[i].size(); k!=l; ++k)
            delete trackvalues[i][k];
    }
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
            if (trackvalues[i][j] == 0) continue;

            volatile int x = *(trackvalues[i][j]);

            if ( x < 0 || x > a) continue;
            else if(x == index){
                rects[index].setFillColor(sf::Color(tracklist[i].second));
                return;
            }
        }
        /*if (*tracklist[i].first == index){
            rects[index].setFillColor(sf::Color(tracklist[i].second));
            return;
        }*/
    }
    rects[index].setFillColor(sf::Color::White);
}