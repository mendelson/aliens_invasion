/*
 * main.cpp
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#include <SDL_main.h>

#include "classes/Game.h"
#include "classes/TitleState.h"

using namespace std;

int main(int argc, char *argv[]) {

	Game* g = new Game("Mateus Mendelson - 11/0017579", 1024, 600);

	// Setting up initial state
	TitleState* s = new TitleState();
	g->Push(s);

	// Main game loop
	g->Run();

    return 0;
}
