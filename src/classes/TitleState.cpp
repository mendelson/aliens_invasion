/*
 * TitleState.cpp
 *
 *  Created on: 23/05/2015
 *      Author: MateusMendelson
 */

#include "TitleState.h"

#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

TitleState::TitleState() : bg("img/title.jpg"), text("font/Call me maybe.ttf", 32, Text::SOLID, "Press space to start!", {0, 0, 0}, Game::GetInstance().getW()/2, Game::GetInstance().getH()/1.5), timer() {
	quitRequested = false;
	popRequested = false;

	text.SetPos(Game::GetInstance().getW()/2, Game::GetInstance().getH()/1.5, true, true);
}

void TitleState::Update() {
	this->quitRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().KeyPress(SPACE)) {
		StageState* s = new StageState();

		Game::GetInstance().Push(s);
	}

	timer.Update(Game::GetInstance().GetDeltaTime());

	if(timer.Get() > 1) {
		timer.Restart();
	}
}

void TitleState::Render() {
	bg.Render(0, 0);

	if (timer.Get() <= 0.5) {
		text.Render();
	}
}
