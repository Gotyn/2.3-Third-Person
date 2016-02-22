#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <map>
#include <memory>

#include <mge/config.hpp>
#include <SFML/Audio.hpp>

/**
 * Audio class (SFML)
 */

class Audio
{
	public:
	    static Audio* Instance();
        //functions
        void LoadAudio();                                               //pre-loads/index all sounds/music
        void AddSound(std::string fileName);                            //pre-loads a specific sound (used in LoadAudio())
        sf::Sound &GetSound(std::string fileName);                      //Use getSound("...").play() to play

        static void PreloadAudio();
        static void PlaySound (std::string fileName);
        static void StopSound (std::string fileName);
        static void PlayMusic (std::string fileName, bool loop = true);
        static void StopMusic (std::string fileName);
        static void PauseMusic(std::string filename);
        void AddMusic(std::string fileName);                            //Indexes a specific music (used in LoadAudio())
        void MapMusic(std::string, std::unique_ptr<sf::Music>);         //puts the music (ptr) in a map.
        sf::Music &GetMusic(std::string fileName);                      //Use getMusic("...").play() to play


        //sf::Sound variables
        std::map<std::string, sf::SoundBuffer> Buffers;
        std::map<std::string, sf::Sound> Sounds;

        std::map<std::string, std::unique_ptr<sf::Music>> Music;

	private:
	    Audio();
	    virtual ~Audio();

	    static Audio* instance;
        std::string soundsPath;
        std::string musicPath;
};

#endif // AUDIO_H
