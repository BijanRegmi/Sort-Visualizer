#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "blocks.h"

class Viewer: public sf::Sprite{
private:
    sf::RenderTexture texture;              // Texture for sprite

    std::vector<sf::RectangleShape> rects;  // Rectangles representing the sorting data

    int width, height; float r_dx;          // Width and height of the sprite and width of individual rectangle block

    std::vector< std::pair<int&, uint32_t> > tracklist; // Pair < address to check value for, uint32 color>
    std::vector< std::list<int> > trackvalues;          // List < value of the data that is being tracked >

    Blocks& blk;                            // Reference variable to the blocks

    void colorizer(int i);                  // Color the rects based on its index and selected alg

    void updatetrackingvalues();            // Update the values that is to be tracked

public:
    // Constructors
    Viewer(int, int, Blocks&);

    // Renderer
    void render();

    // Trackers
    void add_to_track(int& to_watch, int hist_size, uint32_t color);
    void cleartracking();
};

#endif // VIEWER_H
