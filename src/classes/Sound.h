/*
 * Sound.h
 *
 *  Created on: 24/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_SOUND_H_
#define SRC_CLASSES_SOUND_H_

#include <SDL_mixer.h>
#include <string>

class Sound {
public:
	Sound() {chunk = NULL; channel = -1;}
	Sound(std::string file) {Open(file);}

	void Play(int times);
	void Stop();
	void Open(std::string file);
	bool IsOpen();

private:
	Mix_Chunk* chunk;
	int channel;
};

#endif /* SRC_CLASSES_SOUND_H_ */
