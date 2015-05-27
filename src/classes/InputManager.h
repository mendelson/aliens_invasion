/*
 * InputManager.h
 *
 *  Created on: 15/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_INPUTMANAGER_H_
#define SRC_CLASSES_INPUTMANAGER_H_

#include "SDL.h"
#include <unordered_map>

#define LEFT_ARROW_KEY 		SDLK_LEFT
#define RIGHT_ARROW_KEY 	SDLK_RIGHT
#define UP_ARROW_KEY 		SDLK_UP
#define DOWN_ARROW_KEY 		SDLK_DOWN
#define ESCAPE_KEY 			SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON 	SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON	SDL_BUTTON_RIGHT
#define SPACE				SDLK_SPACE

class InputManager {
public:
	void Update();
	bool KeyPress(int key) { return (keyUpdate[key] == updateCounter) && keyState[key]; }
	bool KeyRelease(int key) { return (keyUpdate[key] == updateCounter) && !keyState[key]; }
	bool IsKeyDown(int key) { return keyState[key]; }
	bool MousePress(int button) { return (mouseUpdate[button] == updateCounter) && mouseState[button]; }
	bool MouseRelease(int button) { return (mouseUpdate[button] == updateCounter) && !mouseState[button]; }
	bool IsMouseDown(int button) { return mouseState[button]; }
	int GetMouseX() { return mouseX; }
	int GetMouseY() { return mouseY; }
	bool QuitRequested() { return quitRequested; }
	static InputManager& GetInstance();
private:
	InputManager();
	~InputManager();

	bool mouseState[6];
	int mouseUpdate[6];
	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;
	bool quitRequested;
	int updateCounter;
	int mouseX;
	int mouseY;
};

#endif /* SRC_CLASSES_INPUTMANAGER_H_ */
