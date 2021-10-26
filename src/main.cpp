#include "Viewer.h"
#include "blocks.h"
#include "algorithm.h"

int main(){
    sf::RenderWindow win(sf::VideoMode(300,300), "SORT");
    win.setFramerateLimit(60);
    sf::Event ev;

    Blocks data(20,300);
    Viewer vie(300, 300, &data);
    Algorithms alg(&data);

    while(win.isOpen()){
        while(win.pollEvent(ev)){
            if(ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)){
                alg.stop();
                win.close();
            }

            if (ev.type == sf::Event::KeyPressed){
                    switch(ev.key.code){
                    case sf::Keyboard::Space:
                        alg.start();
                        break;
                    case sf::Keyboard::S:
                        alg.setalg(0);
                        break;
                    case sf::Keyboard::B:
                        alg.setalg(1);
                        break;
                    case sf::Keyboard::M:
                        alg.setalg(2);
                        break;
                    default:
                        std::cout << "No keybind set for this key!\n";
                    }
            }
        }

        vie.render();

        win.clear();
        win.draw(vie);
        win.display();

    }
}
