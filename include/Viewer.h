#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "blocks.h"
#include "algorithm.h"

class Viewer: public sf::Sprite{
private:
    sf::RenderTexture texture;              // Texture for sprite

    std::vector<sf::RectangleShape> rects;  // Rectangles representing the sorting data

    int width, height; float r_dx;          // Width and height of the sprite and width of individual rectangle block

    std::vector< std::pair<int&, int> > watchlist;
    std::vector< std::list<int> > watch_values;

    Blocks& blk;                            // Reference variable to the blocks
    Algorithms& alg;                        // Reference variable to the algorithm object

    void colorizer();              // Color the rects based on its index and selected alg

public:
    // Constructors
    Viewer(int, int, Blocks&, Algorithms&);

    // Renderer
    void render();

    void add_to_track(int& to_watch, int hist_size);
    void updatewatchvalues();
    void clear_track_list();
};

#endif // VIEWER_H
