#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <mge/config.hpp>


#include <SFML/Audio.hpp>


/**
 * Audio class (sfml)
 */


class Audio
{
	public:
	    static Audio* Instance();

        //functions
        void playSound(std::string filename, bool loop = false);
        void playSFX(std::string filename, bool loop = false);
        void Update();

	private:
	    Audio();
	    virtual ~Audio();

	    static Audio* instance;
        std::string audioPath;

        sf::SoundBuffer buffer;
        sf::Sound sound;

};

#endif // AUDIO_H
