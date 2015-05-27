/*
 * StageState.cpp
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#include "StageState.h"

#include <cstdlib>
#include <ctime>

#include "Alien.h"
#include "Camera.h"
#include "EndState.h"
#include "Game.h"
#include "InputManager.h"
#include "Point.h"
#include "StateData.h"

StageState::StageState() : bg("img/ocean.jpg"), tileSet(64, 64, "img/tileset.png"), tileMap("map/tileMap.txt", &tileSet) {
	srand (time(NULL));

	quitRequested = false;
	popRequested = false;

	int numberOfAliens = rand() % 5;
	numberOfAliens++;

	int positionX[] = {
			512, 1012, 512, 1012, 762
	};

	int positionY[] = {
			300, 300, 1000, 1000, 650
	};

	for (int i = 0; i < numberOfAliens; i++) {
		int numberOfMinions = rand() % 4;
		numberOfMinions += 3;

		Alien* alien = new Alien(positionX[i], positionY[i], numberOfMinions);
		objectArray.emplace_back(alien);
	}

	Penguins* p = new Penguins(120, 120);
	objectArray.emplace_back(p);

	Camera::Follow(p->player);

	// Music
	music = new Music("audio/stageState.ogg");
	music->Play(-1);
}

StageState::~StageState() {
	objectArray.clear();
	Pause();
}

void StageState::Update() {
	Camera::Update(Game::GetDeltaTime());

	this->quitRequested =  InputManager::GetInstance().QuitRequested();
	this->popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);

	// Updating objects
	UpdateArray(Game::GetDeltaTime());

	if(Alien::alienCount <= 0) {
		popRequested = true;

		StateData stateData;
		stateData.playerVictory = true;
		EndState* endState = new EndState(stateData);

		Game::GetInstance().Push(endState);
	} else if (Penguins::player == NULL) {
		popRequested = true;

		StateData stateData;
		stateData.playerVictory = false;
		EndState* endState = new EndState(stateData);

		Game::GetInstance().Push(endState);
	}
}

void StageState::Render() {
	bg.Render(0, 0);

	tileMap.RenderLayer(0, (int) Camera::pos.x, (int) Camera::pos.y);

	this->RenderArray();

	tileMap.RenderLayer(1, (int) Camera::pos.x, (int) Camera::pos.y);
}

void StageState::Pause() {
	music->Stop();
}

void StageState::Resume() {
	music->Play(-1);
}
