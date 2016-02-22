#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <mge/config.hpp>

#include <SFML/Audio.hpp>
#include <map>
#include <memory>


/**
 * Audio class (sfml)
 */



class Audio
{
	public:
	    static Audio* Instance();
        //functions
        void LoadSounds();                                              //pre-loads all sounds
        void AddSound(std::string soundName, std::string fileName);     //pre-loads a specific sound (used in LoadSounds()) -- include extension in the fileName.
        sf::Sound &GetSound(std::string soundName);                     //Use getSound("...").play() to play

        //added by jacques for Lua
        static void PreloadAudio();
        static void Play(std::string soundName);

        void AddMusic(std::string musicName, std::string fileName);
        void MapMusic(std::string, std::unique_ptr<sf::Music>);         //puts the music (ptr) in a map.
        sf::Music &GetMusic(std::string musicName);                     //Use getMusic("...").play() to play


        //sf::Sound variables
        std::map<std::string, sf::SoundBuffer> Buffers;
        std::map<std::string, sf::Sound> Sounds;

        std::map<std::string, std::unique_ptr<sf::Music>> Music;

	private:
	    Audio();
	    virtual ~Audio();

	    static Audio* instance;
        std::string audioPath;
};

#endif // AUDIO_H
