#include "bubblesort.cpp"
#include "mergesort.cpp"

int main(){
    sf::RenderWindow win(sf::VideoMode(700,335), "SORT");
    win.setFramerateLimit(60);
    sf::Event ev;

    sf::Font font;
    font.loadFromFile("src/font.ttf");

    sf::Text atex("MERGE SORT", font);
    sf::Text btex("BUBBLE SORT", font);
    atex.setPosition(25, 300);
    btex.setPosition(350, 300);

    mergesort a(300, 300, 300);
    bubblesort b(300, 300, 300);

    a.setPosition(25, 0);
    b.setPosition(350,0);

    while(win.isOpen()){
        while(win.pollEvent(ev)){
            if(ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)){
                win.close();
                a.stop();
            }
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space){
                a.start();
                b.start();
            }
        }

        a.render();
        b.render();

        win.clear();
        win.draw(a);
        win.draw(b);
        win.draw(atex);
        win.draw(btex);
        win.display();

    }
}
