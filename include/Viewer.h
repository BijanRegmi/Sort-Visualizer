#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "blocks.h"
#include "algorithm.h"

class Viewer: public sf::Sprite{
private:
    sf::RenderTexture texture;              // Texture for sprite

    std::vector<sf::RectangleShape> rects;  // Rectangles representing the sorting data

    int width, height; float r_dx;          // Width and height of the sprite and width of individual rectangle block

    Blocks& blk;                            // Reference variable to the blocks
    Algorithms& alg;                        // Reference variable to the algorithm object

    void colorizer(int index);              // Color the rects based on its index and selected alg

public:
    // Constructors
    Viewer(int, int, Blocks&, Algorithms&);

    // Renderer
    void render();
};

#endif // VIEWER_H
