#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "blocks.h"
#include "algorithm.h"

class Viewer: public sf::Sprite{
private:
    sf::RenderTexture texture;              // Texture for sprite

    std::vector<sf::RectangleShape> rects;  // Rectangles representing the sorting data

    int width, height;                      // Width and height of the sprite

    Blocks* blk;                            // Pointer to the blocks
    Algorithms* alg;

    void colorizer(int index);

public:
    // Constructors
    Viewer();
    Viewer(int, int, Blocks*, Algorithms*);

    // Renderer
    void render();
};

#endif // VIEWER_H
