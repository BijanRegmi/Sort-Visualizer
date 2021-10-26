#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include "blocks.h"

class Viewer: public sf::Sprite{
private:
    sf::RenderTexture texture;  // Texture for sprite

    int width, height;          // Width and height of the sprite

    Blocks* blk;                // Pointer to the blocks

public:
    // Constructors
    Viewer();
    Viewer(int, int, Blocks*);

    // Renderer
    void render();
};

#endif // VIEWER_H
