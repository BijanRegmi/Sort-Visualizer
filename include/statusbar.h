#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <SFML/Graphics.hpp>
#include "blocks.h"
#include "algorithm.h"

#include <sstream>
#include <iostream>

class Bar: public sf::Sprite{
private:
    sf::RenderTexture texture;  // Texture for sprite

    int width, height;          // Width and height of the sprite

    Blocks* data;               // Pointer to the blocks

    Algorithms* alg;            // Pointer to the algorithm object

    sf::Font font;
    sf::Text text;
    sf::Text desc;

public:
    // Constructors
    Bar(int, int, Blocks*, Algorithms*);

    // Renderer
    void render();
};

#endif // STATUSBAR_H
