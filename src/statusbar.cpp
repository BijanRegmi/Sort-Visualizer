#include "statusbar.h"

Bar::Bar(){}

Bar::Bar(int w, int h, Blocks* b, Algorithms* a){
    width = w;
    height = h;
    data = b;
    alg = a;

    texture.create(width, height);
    this->setTexture(texture.getTexture());

    if (!font.loadFromFile("src/font.ttf"))
    {
        std::cout << "Error loading font!";
    }

    text.setFont(font);
    text.setCharacterSize(10);
}

void Bar::render(){
    std::stringstream sstr;

    sstr << "Selected Alg: "     << alg->getalg()
         << " | Compare count: " << data->comparecounter
         << " | Read count: "    << data->readcounter
         << " | Swap count: "    << data->swapcounter
         << " | Delay: "         << alg->delay << " microseconds"
         << " | Data size: "     << data->amount
         << " | Working: "       << (alg->working ? "Yes" : "No ")
         << " | Sorted: "        << (alg->sorted ? "Yes" : "No ") ;

    text.setString(sstr.str());

    texture.clear();
    texture.draw(text);
    texture.display();
}
