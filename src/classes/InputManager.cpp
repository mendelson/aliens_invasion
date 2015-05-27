/*
 * InputManager.cpp
 *
 *  Created on: 15/04/2015
 *      Author: MateusMendelson
 */

#include "InputManager.h"

InputManager& InputManager::GetInstance() {
	static InputManager inputManager;
	return inputManager;
}

void InputManager::Update() {
	updateCounter++;

	SDL_Event event;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// Resetar a flag de quit
	quitRequested = false;

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_MOUSEBUTTONUP) {
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		} else if (event.type == SDL_KEYUP) {
			keyState[event.key.keysym.sym] = false;
			keyUpdate[event.key.keysym.sym] = updateCounter;
		} else if (event.type == SDL_KEYDOWN) {
			if (event.key.repeat != 1) {
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
		} else if (event.type == SDL_QUIT) {
			// Se o evento for quit, setar a flag para terminação
			quitRequested = true;
		}
	}
}

InputManager::InputManager() {
	updateCounter = 0;
	quitRequested = false;
	SDL_GetMouseState(&mouseX, &mouseY);

	for (int i = 0; i < 6; i++) {
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}
}

InputManager::~InputManager() {
	// Just a blank
}
