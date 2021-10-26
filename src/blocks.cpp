#include "sorts.h"

Sort::Sort(int width, int height, int amount){
    this->width = width;
    this->height = height;
    this->amount = amount;


    textr.create(width, height);
    this->setTexture(textr.getTexture());

    for (int i=0; i<amount; i++){
        sf::RectangleShape a(sf::Vector2f(width/amount, std::rand()%height));
        //a.setFillColor(sf::Color(255, 0, 0, h*255/height));
        lines.push_back(a);
    }
}

void Sort::render(){
    textr.clear();
    for (int i=0; i<lines.size(); i++){
        lines[i].setPosition(sf::Vector2f(i*width/amount, height - lines[i].getSize().y));
        int h = lines[i].getSize().y*255/height;
        lines[i].setFillColor(sf::Color(0, h, 255-h));
        textr.draw(lines[i]);
    }
    textr.display();
}

void Sort::stop(){
    std::cout << "Stopping the thread" << std::endl;
    sortingThread.detach();
    std::cout << "Thread stopped. You can close the window now." << std::endl;
}
