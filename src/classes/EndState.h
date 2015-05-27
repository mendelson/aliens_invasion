/*
 * EndState.h
 *
 *  Created on: 25/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_ENDSTATE_H_
#define SRC_CLASSES_ENDSTATE_H_

#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "StateData.h"

class EndState : public State {
public:
	EndState(StateData stateData);
	virtual ~EndState() {};

	void Update();
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Music music;
	Text instruction;
};

#endif /* SRC_CLASSES_ENDSTATE_H_ */
