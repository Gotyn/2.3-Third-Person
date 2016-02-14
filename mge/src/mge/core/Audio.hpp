#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <mge/config.hpp>
#include "fmod_studio.h"
#include "fmod_errors.h"


/**
 * Audio class (FMOD)
 */


class Audio
{
	public:
	    static Audio* Instance();

        //functions
        void playSound(std::string filename);
        void playSFX(std::string filename);

	private:
	    Audio();
	    virtual ~Audio();

	    static Audio* instance;

	    std::string audioPath;

	    //voids
	    void FMOD_ErrorCheck(FMOD_RESULT check);

};

#endif // AUDIO_H
