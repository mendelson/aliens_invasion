/*
 * Game.cpp
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#include "Game.h"
#include "Resources.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


Game* Game::instance = 0;
float Game::dt;
static float previous;

Game::Game(string title, int width, int height) {
	frameStart = (int) SDL_GetTicks()/1000;
	Game::dt = 0;
	this->width = width;
	this->height = height;

	if(instance != NULL) {
		cout << "Error: the class 'Game' has already been instanciated!" << endl;
		abort();
	}

	instance = this;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		cout << "Error: could not call SDL_Init properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
		abort();
	}

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
		cout << "Error: could not call IMG_Init properly.\nAborting..." << endl;
		abort();
	}

	if((window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0)) == NULL) {
		cout << "Error: could not create window properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
		abort();
	}

	if((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		cout << "Error: could not create renderer properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
		abort();
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
		cout << "Error: could not open mix audio properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
		abort();
	}

	if(TTF_Init() != 0) {
		cout << "Error: could not initialise ttf properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
		abort();
	}

	storedState = NULL;

	// Initializing pseudo-random number generator
	srand(time(NULL));
}

Game::~Game() {
	Mix_CloseAudio();
	Mix_Quit();

	if (storedState != NULL) {
		delete (storedState);
	}

	while (!stateStack.empty()) {
		stateStack.pop();
	}

	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Game& Game::GetInstance() { // static
	return *instance;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

State& Game::GetCurrentState() {
	return *(stateStack.top().get());
}

void Game::Push(State* state) {
	storedState = state;
}

void Game::Run() {
	// Checking initial state
	if (storedState == NULL) {
		return;
	}

	stateStack.emplace(storedState);
	storedState = NULL;

	previous = frameStart;

	while(!stateStack.empty() && !GetCurrentState().QuitRequested()) {
		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		GetCurrentState().Update();
		GetCurrentState().Render();

		SDL_RenderPresent(renderer);

		if(GetCurrentState().PopRequested()) {
			stateStack.pop();

			if(!stateStack.empty()){
				GetCurrentState().Resume();
			}
		}

		if(storedState != NULL){
			GetCurrentState().Pause();
			stateStack.emplace(storedState);
			storedState = NULL;
			GetCurrentState().Resume();
		}

		SDL_Delay(33);
	}

	Resources::ClearImages();
	Resources::ClearMusic();
	Resources::ClearSound();
}

void Game::CalculateDeltaTime() {
	previous = frameStart;
	frameStart = (float) SDL_GetTicks()/1000;
	Game::dt = frameStart - previous;
}
