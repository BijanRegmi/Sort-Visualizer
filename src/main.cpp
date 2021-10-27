#include "Viewer.h"
#include "blocks.h"
#include "algorithm.h"
#include "statusbar.h"

int main(){
    int WIDTH = 1000;
    int HEIGHT = 600;
    int FPS = 60;
    int DATA_SIZE = 100;
    int BAR_H = 100;

    sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), "SORT");
    win.setFramerateLimit(FPS);
    sf::Event ev;

    Blocks data(DATA_SIZE, HEIGHT-BAR_H);
    Algorithms alg(data);
    Viewer vie(WIDTH, HEIGHT-BAR_H, data, alg);
    Bar bar(WIDTH, BAR_H, &data, &alg);
    bar.setPosition(0, HEIGHT-BAR_H);

    while(win.isOpen()){
        while(win.pollEvent(ev)){
            // Keybindings
            if (ev.type == sf::Event::KeyPressed){
                    switch(ev.key.code){
                    case sf::Keyboard::Escape:
                        alg.stop();
                        win.close();
                        break;

                    case sf::Keyboard::Space:
                        alg.start();
                        break;
                    case sf::Keyboard::C:
                        alg.setalg(0);
                        break;
                    case sf::Keyboard::S:
                        alg.setalg(1);
                        break;

                    case sf::Keyboard::B:
                        alg.setalg(2);
                        break;

                    case sf::Keyboard::M:
                        alg.setalg(3);
                        break;

                    case sf::Keyboard::Q:
                        alg.setalg(4);
                        break;

                    case sf::Keyboard::R:
                        alg.setalg(5);
                        break;

                    case sf::Keyboard::Add:
                        if (ev.key.shift && ev.key.control)
                            data.setdelay(-7);
                        else if (ev.key.control)
                            data.setdelay(-5);
                        else if (ev.key.shift)
                            data.setdelay(-3);
                        else
                            data.setdelay(-1);
                        break;

                    case sf::Keyboard::Subtract:
                        if (ev.key.shift && ev.key.control)
                            data.setdelay(-8);
                        else if (ev.key.control)
                            data.setdelay(-6);
                        else if (ev.key.shift)
                            data.setdelay(-4);
                        else
                            data.setdelay(-2);
                        break;

                    case sf::Keyboard::Up:
                        alg.setalg(-1);
                        break;

                    case sf::Keyboard::Down:
                        alg.setalg(-2);
                        break;

                    default:
                        std::cout << "No keybind set for this(" << ev.key.code << ") key!\n";
                    }
            }
        }

        vie.render();
        bar.render();

        win.clear();
        win.draw(vie);
        win.draw(bar);
        win.display();

    }
}
