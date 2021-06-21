#ifndef SORT_H
#define SORT_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <thread>
#include <chrono>

class Sort: public sf::Sprite{
private:
    int width, height, amount;
    sf::RenderTexture textr;
public:
    Sort(int width, int height, int amount);
    void render();
    void stop();
protected:
    std::thread sortingThread;
    std::vector<sf::RectangleShape> lines;
    void algorithm();
};

#endif // SORT_H
