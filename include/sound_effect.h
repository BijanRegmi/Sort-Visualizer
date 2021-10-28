#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

class sound_effect{
private:
    sf::SoundBuffer read_buffer;
    sf::SoundBuffer write_buffer;
    sf::SoundBuffer check_buffer;
    sf::SoundBuffer sorted_buffer;
    sf::SoundBuffer notsorted_buffer;
    sf::Sound read;
    sf::Sound write;
    sf::Sound check;
    sf::Sound sorted;
    sf::Sound notsorted;
public:
    sound_effect();
    void play(int task, float pitch);
    int get_c_dur();
};

#endif // SOUND_H