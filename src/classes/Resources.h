/*
 * Resources.h
 *
 *  Created on: 13/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_RESOURCES_H_
#define SRC_CLASSES_RESOURCES_H_

#include "SDL.h"
#include "Game.h"
#include "Music.h"
#include <string>
#include <unordered_map>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Resources {
public:
	static SDL_Texture* GetImage(std::string file);
	static void ClearImages();
	static Mix_Music* GetMusic(std::string file);
	static void ClearMusic();
	static Mix_Chunk* GetSound(std::string file);
	static void ClearSound();
	static TTF_Font* GetFont(std::string file, int ptsize);
	static void ClearFonts();


private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
	static std::unordered_map<std::string, TTF_Font*> fontTable;
};

#endif /* SRC_CLASSES_RESOURCES_H_ */
