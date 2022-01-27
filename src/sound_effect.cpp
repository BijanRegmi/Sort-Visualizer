#include "sound_effect.h"
#include <iostream>

sound_effect::sound_effect(){
    if (
    read_buffer.loadFromFile("Sound_Effects/read.wav") && 
    write_buffer.loadFromFile("Sound_Effects/write.wav") &&
    check_buffer.loadFromFile("Sound_Effects/check.wav") &&
    sorted_buffer.loadFromFile("Sound_Effects/hoorah.wav") &&
    notsorted_buffer.loadFromFile("Sound_Effects/no.wav")){std::cout << "\nSound loaded perfectly ^^\n";}

    read.setBuffer(read_buffer);
    write.setBuffer(write_buffer);
    check.setBuffer(check_buffer);
    sorted.setBuffer(sorted_buffer);
    notsorted.setBuffer(notsorted_buffer);

    isMuted = false;
}

void sound_effect::play(int task, float pitch){
    if (isMuted) return;
    switch (task)
    {
    case 0:
        read.setPitch(pitch);
        read.play();
        break;
    case 1:
        write.setPitch(pitch);
        write.play();
        break;
    case 2:
        check.setPitch(pitch);
        check.play();
        break;
    case 3:
        sorted.play();
        break;
    case 4:
        notsorted.play();
        break;
    default:
        break;
    }
}

void sound_effect::stop(){
    read.stop();
    write.stop();
}

void sound_effect::toggleMute(){
    stop();
    isMuted ^= true;
}

