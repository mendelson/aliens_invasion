/*
 * StageState.h
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#ifndef STAGESTATE_H_
#define STAGESTATE_H_



#include <vector>

#include "Penguins.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include "State.h"
#include "Music.h"
#include <memory>


class StageState : public State {
public:
	StageState();
	~StageState();

	void Update();
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	TileSet tileSet;
	TileMap tileMap;
	Music* music;
};

#endif /* STAGESTATE_H_ */
