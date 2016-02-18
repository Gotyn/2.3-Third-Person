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

// Add all sounds here! -- expose this to LUA?
void Audio::LoadSounds() {
    AddSound("gate", "gate.wav");
    AddSound("door", "door.wav");

    AddMusic("memory", "memory.ogg");
    AddMusic("piano", "piano.ogg");
}

void Audio::AddSound(std::string soundName, std::string fileName) {
    Buffers[soundName].loadFromFile(config::MGE_AUDIO_PATH + fileName);
    if (Buffers[soundName].getSampleCount() == 0)
        std::cout << "WARNING: You're playing an empty buffer on '" << soundName << "'!" << std::endl;
    Sounds[soundName].setBuffer(Buffers[soundName]);
}

sf::Sound &Audio::GetSound(std::string soundName) {
    Sounds[soundName].setBuffer(Buffers[soundName]);
    return Sounds[soundName];
}

void Audio::AddMusic(std::string musicName, std::string fileName){
    auto music = std::unique_ptr<sf::Music>(new sf::Music());
    music->openFromFile(config::MGE_AUDIO_PATH + fileName);
    MapMusic(musicName,std::move(music));
}

//musicName is the map key.
void Audio::MapMusic(std::string musicName, std::unique_ptr<sf::Music> value){
    Music.insert(std::pair<std::string, std::unique_ptr<sf::Music> >(musicName, std::move(value)));
}

sf::Music &Audio::GetMusic(std::string musicName){
    return *Music.at(musicName);
}
