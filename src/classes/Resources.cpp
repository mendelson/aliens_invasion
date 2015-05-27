/*
 * Resources.cpp
 *
 *  Created on: 13/04/2015
 *      Author: MateusMendelson
 */

#include "Resources.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

SDL_Texture* Resources::GetImage(std::string file) {
	// Checking existence of the current image
	// In this case, the image has not been loaded yet. So let's do it!
	if(imageTable.find(file) == imageTable.end()) {
		SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

		if(texture == NULL) {
			std::cout << "Error: could not create texture properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
			abort();
		}

		imageTable.emplace(file, texture);

		return texture;
	}
	// In this case, the image had been previously loaded
	else {
		return imageTable.at(file);
	}
}

void Resources::ClearImages() {
	//SDL_Texture* temp = NULL;
	std::unordered_map<std::string, SDL_Texture*>::iterator tempIt;
	for(unsigned int i = 0; i < imageTable.size(); i++) {
		tempIt = imageTable.begin();
		SDL_DestroyTexture(tempIt->second);
		imageTable.erase(imageTable.begin());
	}
}

Mix_Music* Resources::GetMusic(std::string file) {
	// Checking existence of the current music
	// In this case, the music has not been loaded yet. So let's do it!
	if (musicTable.find(file) == musicTable.end()) {
		Mix_Music* music = Mix_LoadMUS(file.c_str());

		if (music == NULL) {
			std::cout << "Error: could not load music properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
			abort();
		}

		musicTable.emplace(file, music);

		return music;
	}
	// In this case, the image had been previously loaded
	else {
		return musicTable.at(file);
	}
}

void Resources::ClearMusic() {
	std::unordered_map<std::string, Mix_Music*>::iterator tempIt;

	for (unsigned int i = 0; i < musicTable.size(); i++) {
		tempIt = musicTable.begin();
		Mix_FreeMusic(tempIt->second);
		musicTable.erase(musicTable.begin());
	}
}

Mix_Chunk* Resources::GetSound(std::string file) {
	// Checking existence of the current music
	// In this case, the music has not been loaded yet. So let's do it!
	if (soundTable.find(file) == soundTable.end()) {
		Mix_Chunk* music = Mix_LoadWAV(file.c_str());

		if (music == NULL) {
			std::cout << "Error: could not load sound properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
			abort();
		}

		soundTable.emplace(file, music);

		return music;
	}
	// In this case, the image had been previously loaded
	else {
		return soundTable.at(file);
	}
}

void Resources::ClearSound() {
	std::unordered_map<std::string, Mix_Chunk*>::iterator tempIt;

	for (unsigned int i = 0; i < soundTable.size(); i++) {
		tempIt = soundTable.begin();
		Mix_FreeChunk(tempIt->second);
		soundTable.erase(soundTable.begin());
	}
}

TTF_Font* Resources::GetFont(std::string file, int ptsize) {
	char dontknowwhy[21];
	sprintf(dontknowwhy, "%d", ptsize);
	string key = file + dontknowwhy;

	// Checking existence of the current font
	// In this case, the font has not been loaded yet. So let's do it!
	if (fontTable.find(key) == fontTable.end()) {
		TTF_Font* font = TTF_OpenFont (file.c_str(), ptsize);

		if (font == NULL) {
			std::cout << "Error: could not load font properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
			abort();
		}

		fontTable.emplace(key, font);

		return font;
	}
	// In this case, the image had been previously loaded
	else {
		return fontTable.at(key);
	}
}

void Resources::ClearFonts() {
	std::unordered_map<std::string, TTF_Font*>::iterator tempIt;

	for (unsigned int i = 0; i < fontTable.size(); i++) {
		tempIt = fontTable.begin();
		TTF_CloseFont(tempIt->second);
		fontTable.erase(fontTable.begin());
	}
}
