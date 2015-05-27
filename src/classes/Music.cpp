/*
 * Music.cpp
 *
 *  Created on: 23/05/2015
 *      Author: MateusMendelson
 */

#include "Music.h"
#include "Resources.h"

void Music::Play(int times) {
	Mix_PlayMusic(music, times);
}

void Music::Stop() {
	Mix_FadeOutMusic (500);
}

void Music::Open(std::string file) {
	music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
	return music == NULL;
}
