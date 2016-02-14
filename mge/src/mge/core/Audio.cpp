#include "Audio.hpp"

Audio* Audio::instance = NULL;

//Make it a Singleton -- Only one instance allowed.
Audio* Audio::Instance() {
    if (!instance) {
        instance = new Audio;
    }
    return instance;
}

void Audio::FMOD_ErrorCheck(FMOD_RESULT check){
    if (check != FMOD_OK){
        std::cout<<std::endl<<"FMOD ERROR: "+check<<std::endl;
    }
}

Audio::Audio(){
    audioPath = config::MGE_AUDIO_PATH.c_str();
}

Audio::~Audio(){
}

void Audio::playSound(std::string fileName) {
    std::cout << "----playSound----" << std::endl;

    std::string file = config::MGE_AUDIO_PATH+fileName;
    std::cout<< file << std::endl;

    std::cout << "----/playSound----" << std::endl;

}

void Audio::playSFX(std::string fileName) {
    std::cout << "----playSfx----" << std::endl;
    std::cout << "----/playSfx----" << std::endl;
}
