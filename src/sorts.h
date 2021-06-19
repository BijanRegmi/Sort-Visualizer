#ifndef SORT_H
#define SORT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

class Sort: public sf::Sprite{
private:
    int width, height, amount;
    sf::RenderTexture textr;
public:
    Sort(int width, int height, int amount);
    void render();
protected:
    std::vector<sf::RectangleShape> lines;
    void algorithm();
};

#endif // SORT_H
