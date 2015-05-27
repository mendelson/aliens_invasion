/*
 * EndState.cpp
 *
 *  Created on: 25/05/2015
 *      Author: MateusMendelson
 */

#include "EndState.h"
#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

EndState::EndState(StateData stateData) : bg(), music(), instruction("font/Call me maybe.ttf", 20, Text::SOLID, "You have won!", {255,255,255}, 0, Game::GetInstance().getH() - 40){
	if (stateData.playerVictory) {
		bg.Open("img/win.jpg");
		music.Open("audio/endStateWin.ogg");
		instruction.SetText("You have won! Press space to try again or 'esc' to return to the home screen.");
	} else {
		bg.Open("img/lose.jpg");
		music.Open("audio/endStateLose.ogg");
		instruction.SetText("You have lost! Press space to try again or 'esc' to return to the home screen.");
	}
}

void EndState::Update(){
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().IsKeyDown(SPACE)) {
		State* stageState = new StageState();
		Game::GetInstance().Push(stageState);
		popRequested = true;
	}
}

void EndState::Render(){
	bg.Render(0,0);
	instruction.Render();
}

void EndState::Pause(){
	music.Stop();
}

void EndState::Resume(){
	music.Play(0);
}
