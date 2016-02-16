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

void Audio::Update(){

}

void Audio::playSound(std::string fileName, bool loop) {
    std::cout << "----playSound----" << std::endl;
    std::string file = config::MGE_AUDIO_PATH+fileName;
    if (!buffer.loadFromFile(file)) return;
    sound.setBuffer(buffer);
    sound.setLoop(loop);
    sound.play();
    std::cout << "----/playSound----" << std::endl;

}

void Audio::playSFX(std::string fileName, bool loop) {
    std::cout << "----playSfx----" << std::endl;
    std::cout << "----/playSfx----" << std::endl;
}
