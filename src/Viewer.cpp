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
    
    std::deque< volatile int* > a;
    for (; s!=0; s--){
        volatile int* ptr = new volatile int;
        *ptr = -1;
        a.push_back(ptr);
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
    for (int i=0, j=tracklist.size(); i!=j; i++){
        int n = trackvalues[i].size();
        volatile int* p_val = tracklist[i].first;       // Pointer to current value
        volatile int* p_pval = trackvalues[i][n-1];    // Pointer to previous value
        if (p_val == 0 || p_pval == 0){
            std::cout << "Pointer is null lul.\n";
            continue;
        }

        if (*p_val != *p_pval){
            delete trackvalues[i].front();
            trackvalues[i].pop_front();

            volatile int* ptr = new volatile int;
            *ptr = *p_val;
            trackvalues[i].push_back(ptr);
        }
    }
}

void Viewer::cleartracking(){
    tracklist.clear();
    for (int i=0, j = trackvalues.size(); i!=j; ++i){
        for (int k=0, l=trackvalues[i].size(); k!=l; ++k){
            delete trackvalues[i][k];
        }
    }
    trackvalues.clear();
}

// Colorizer
void Viewer::colorizer(int index){
    int a = blk.amount;

    for (int i=0, j=trackvalues.size(); i!=j; ++i){
        for (int k=0, l=trackvalues[i].size(); k!=l; ++k){
            volatile int* p_val = trackvalues[i][k];
            if (p_val==0) continue;
            volatile int val = *p_val;
            if (val == index && val >= 0 && val < a){
                rects[index].setFillColor(sf::Color(tracklist[i].second));
                return;
            }
        }
    }
    rects[index].setFillColor(sf::Color::White);
}