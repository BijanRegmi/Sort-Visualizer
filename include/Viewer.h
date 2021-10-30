#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <deque>
#include <list>
#include <tuple>

#include "blocks.h"

class Viewer: public sf::Sprite{
private:
    sf::RenderTexture texture;              // Texture for sprite

    std::vector<sf::RectangleShape> rects;  // Rectangles representing the sorting data

    int width, height; float r_dx;          // Width and height of the sprite and width of individual rectangle block

    std::vector< std::pair<volatile int*, uint32_t> > tracklist; // Pair < address to check value for, uint32 color>
    std::vector< std::deque<volatile int*> > trackvalues;          // List < value of the data that is being tracked >

    Blocks& blk;                            // Reference variable to the blocks

    void colorizer(int i);                  // Color the rects based on its index and selected alg

    void updatetrackvalues();               // Update the values that is to be tracked

public:
    void checkvalues();
    // Constructors
    Viewer(int, int, Blocks&);

    // Renderer
    void render();

    // Trackers
    void add_to_track(volatile int* to_watch, int hist_size, uint32_t color);
    void cleartracking();
};

#endif // VIEWER_H
