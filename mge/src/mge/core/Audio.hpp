#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <mge/config.hpp>

#include <SFML/Audio.hpp>
#include <map>


/**
 * Audio class (sfml)
 */



class Audio
{
	public:
	    static Audio* Instance();

	    enum SoundNames { gate, door };         //TIP: keep this name the same as the filename (excluding extension)

        //functions
        void LoadSounds();                                           //pre-loads all sounds
        void LoadSound(SoundNames soundName, std::string fileName);  //pre-loads a specific sound (used in LoadSounds()) -- include extension in the string.
        void PlaySound(SoundNames soundName);

        std::map<SoundNames, sf::SoundBuffer> Buffers;
        std::map<SoundNames, sf::Sound> Sounds;
	private:
	    Audio();
	    virtual ~Audio();

	    static Audio* instance;
        std::string audioPath;
};

#endif // AUDIO_H
