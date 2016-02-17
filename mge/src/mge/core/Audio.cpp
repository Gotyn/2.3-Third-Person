#include "Audio.hpp"

Audio* Audio::instance = NULL;

//Make it a Singleton -- Only one instance allowed.
Audio* Audio::Instance() {
    if (!instance) {
        instance = new Audio;
    }
    return instance;
}

Audio::Audio(){
    audioPath = config::MGE_AUDIO_PATH.c_str();
}

Audio::~Audio(){
}

// Add all sounds here! -- expose this to lua?
void Audio::LoadSounds() {
    LoadSound(gate, "gate.wav");
    LoadSound(door, "door.wav");
}

void Audio::LoadSound(SoundNames soundName, std::string fileName) {
    Buffers[soundName].loadFromFile(config::MGE_AUDIO_PATH + fileName);
    Sounds[soundName];
}

void Audio::PlaySound(SoundNames soundName) {
    Sounds[soundName].setBuffer(Buffers[soundName]);
    Sounds[soundName].play();
}

//void Audio::playSFX(std::string fileName, bool loop) {
//    std::cout << "----playSfx----" << std::endl;
//    std::cout << "----/playSfx----" << std::endl;
//}
