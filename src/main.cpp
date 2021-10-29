#include "Viewer.h"
#include "blocks.h"
#include "algorithm.h"
#include "statusbar.h"
#include "sound_effect.h"

int main(){
    sf::VideoMode def = sf::VideoMode::getDesktopMode();
    const int FPS = 60;
    const int WIDTH = def.width;
    const int HEIGHT = def.height;
    const int BAR_H = 0.05*HEIGHT;
    const int DATA_SIZE = 1*WIDTH;

    sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), "SORT", sf::Style::Default);
    win.setFramerateLimit(FPS);
    sf::Event ev;
    
    sound_effect s_effect;
    Blocks data(DATA_SIZE, HEIGHT-BAR_H, s_effect);
    Viewer vie(WIDTH, HEIGHT-BAR_H, data);
    Algorithms alg(data, vie);
    vie.setPosition(0, 0);
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
                        if (ev.key.shift)
                            alg.setalg(7);
                        else
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

                    case sf::Keyboard::I:
                        alg.setalg(6);
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

                    case sf::Keyboard::Num0:
                    case sf::Keyboard::Numpad0:
                        data.setdelay(0);
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
