#include "statusbar.h"

//Constructors
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
    desc.setFont(font);
    desc.setCharacterSize(10);
    desc.setPosition(0, 20);
}

// Renderer
void Bar::render(){
    std::stringstream sstr;

    sstr << "Selected Alg: "     << alg->getalg()
         << " | Compare count: " << data->counter.c
         << " | Read count: "    << data->counter.r
         << " | Write count: "   << data->counter.w
         << " | Swap count: "    << data->counter.s
         << " | Delay: ("        << data->r_delay                   << ", " << data->w_delay << ") "
         << " | Data size: "     << data->amount
         << " | Working: "       << (alg->working ? "Yes" : "No ")
         << " | Sorted: "        << (alg->sorted ? "Yes" : "No ") ;

    text.setString(sstr.str());
    desc.setString(alg->algdesc);

    texture.clear();
    texture.draw(text);
    texture.draw(desc);
    texture.display();
}
