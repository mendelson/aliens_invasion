/*
 * Sound.cpp
 *
 *  Created on: 24/05/2015
 *      Author: MateusMendelson
 */

#include "Sound.h"
#include "Resources.h"

void Sound::Play(int times) {
	channel = Mix_PlayChannel (-1, chunk, times);
}

void Sound::Stop() {
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
	chunk = Resources::GetSound(file);
}
