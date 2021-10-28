#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

int main(){
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    sf::Sound sound;
    sf::SoundBuffer buff;
    
    filename = "Sound_Effects/" + filename;
    
    if (!buff.loadFromFile(filename)) {
        std::cout << "Failed to load file.\n";
        return -1;
    }
    sound.setBuffer(buff);
    sound.setLoop(1);

    int dur = buff.getDuration().asMicroseconds();
    float p = 0;

    sound.play();
    while(true){
        sound.setPitch(p);
        std::cout << "Pitch: " << p << std::endl;
        p += 0.01;
        std::this_thread::sleep_for(std::chrono::microseconds(dur));
        if (p>4000) break;
    }
}