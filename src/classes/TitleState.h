/*
 * TitleState.h
 *
 *  Created on: 23/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_TITLESTATE_H_
#define SRC_CLASSES_TITLESTATE_H_

#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"

class TitleState : public State {
public:
	TitleState();

	void Update();
	void Render();

	void Pause() {}
	void Resume() {}

private:
	Sprite bg;
	Text text;
	Timer timer;
};

#endif /* SRC_CLASSES_TITLESTATE_H_ */
