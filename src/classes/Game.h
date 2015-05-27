/*
 * Game.h
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#ifndef GAME_H_
#define GAME_H_


#include "SDL.h"
#include "SDL_image.h"
#include "State.h"
#include "InputManager.h"
#include <string>
#include <iostream>
#include <stack>
#include <memory>


using std::cout;
using std::string;
using std::endl;

class Game {
public:
	Game(string title, int width, int height);
	~Game();

	void Run();
	SDL_Renderer* GetRenderer();
	static Game& GetInstance();
	static float GetDeltaTime() { return dt; }
	State& GetCurrentState();
	void Push (State* state);
	int getW() { return width; }
	int getH() { return height; }

private:
	void CalculateDeltaTime();

	float frameStart;
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* storedState;
	static float dt;
	int width;
	int height;

	std::stack<std::unique_ptr<State>> stateStack;

};

#endif /* GAME_H_ */
