#include "bubblesort.cpp"

int main(){
    sf::RenderWindow win(sf::VideoMode(600,600), "SORT");
    win.setFramerateLimit(60);
    sf::Event ev;

    bubblesort a(600, 600, 600);

    while(win.isOpen()){
        while(win.pollEvent(ev)){
            if(ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)){
                win.close();
                a.stop();
            }
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
                a.start();
        }

        a.render();

        win.clear();
        win.draw(a);
        win.display();

    }
}
