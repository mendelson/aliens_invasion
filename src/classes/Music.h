/*
 * Music.h
 *
 *  Created on: 23/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_MUSIC_H_
#define SRC_MUSIC_H_

#include <SDL_mixer.h>
#include <string>

class Music {
public:
	Music() {music = NULL;}
	Music(std::string file) {Open(file);}

	void Play(int times);
	void Stop();
	void Open(std::string file);
	bool IsOpen();

private:
	Mix_Music* music;
};

#endif /* SRC_MUSIC_H_ */
