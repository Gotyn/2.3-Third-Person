#include "Audio.hpp"
#include "mge/util/Utils.hpp"

Audio* Audio::instance = NULL;

//Make it a Singleton -- Only one instance allowed.
Audio* Audio::Instance() {
    if (!instance) {
        instance = new Audio;
    }
    return instance;
}

Audio::Audio() {
    soundsPath = config::MGE_SOUNDS_PATH.c_str();
    musicPath = config::MGE_MUSIC_PATH.c_str();
}

Audio::~Audio() {
}

/// PRELOADING -- OPTIONAL
void Audio::PreloadAudio() {
    Instance()->LoadAudio();
}

void Audio::LoadAudio() {
    std::vector<std::string> soundNames = Utils::findFilesIn(soundsPath);

    for (size_t i=0; i < soundNames.size(); i++) {
        AddSound(soundNames[i]);
        std::cout << soundNames[i] << " preloaded!" << std::endl;
    }

    //Not tested!
    std::vector<std::string> musicNames = Utils::findFilesIn(musicPath);
    for (size_t i=0; i < musicNames.size(); i++) {
        AddMusic(musicNames[i]);
        std::cout << musicNames[i] << " indexed!" << std::endl;
    }
}
/// END PRELOADING

void Audio::AddSound(std::string fileName) {
    Buffers[fileName].loadFromFile(soundsPath + fileName);
    if (Buffers[fileName].getSampleCount() == 0)
        std::cout << "WARNING: You're playing an empty buffer on '" << fileName << "'!" << std::endl;
    Sounds[fileName].setBuffer(Buffers[fileName]);
}

sf::Sound &Audio::GetSound(std::string fileName) {
    Sounds[fileName].setBuffer(Buffers[fileName]);
    return Sounds[fileName];
}

void Audio::PlaySound(std::string fileName) {
    instance = Instance();

    // Check if sound is loaded
    if(instance->Sounds.find(fileName) == Instance()->Sounds.end()) {       // Sound not loaded.
        instance->AddSound(fileName);                                       // Load sound.
    }

    instance->GetSound(fileName).play();                                    // Play sound.
}

void Audio::StopSound(std::string fileName) {
    Instance()->GetSound(fileName).stop();
}

void Audio::PlayMusic(std::string fileName, bool loop) {
    instance = Instance();

    // Check if music is indexed
    if(instance->Music.find(fileName) == Instance()->Music.end()) {         // Music not indexed.
        instance->AddMusic(fileName);                                       // Load music.
    }

    instance->GetMusic(fileName).setLoop(loop);
    instance->GetMusic(fileName).play();                                    // Play music.
    std::cout << "NOTE: Playing music '" << fileName << "'." << std::endl;
}

void Audio::StopMusic(std::string fileName) {
    Instance()->GetMusic(fileName).stop();
    std::cout << "NOTE: Stopped music '" << fileName << "'." << std::endl;
}

void Audio::AddMusic(std::string fileName) {
    auto music = std::unique_ptr<sf::Music>(new sf::Music());
    music->openFromFile(musicPath + fileName);
    MapMusic(fileName,std::move(music));
}

//musicName is the map key.
void Audio::MapMusic(std::string fileName, std::unique_ptr<sf::Music> value) {
    Music.insert(std::pair<std::string, std::unique_ptr<sf::Music> >(fileName, std::move(value)));
}

sf::Music &Audio::GetMusic(std::string fileName) {
    return *Music.at(fileName);
}
