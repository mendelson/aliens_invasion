/*
 * State.h
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#ifndef STATE_H_
#define STATE_H_

#include <vector>

#include "Penguins.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include <memory>

class State {
public:
	State();
	virtual ~State();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void AddObject(GameObject* ptr);
	bool PopRequested() { return popRequested; }
	bool QuitRequested() { return quitRequested; }

protected:
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	bool popRequested;
	bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif /* STATE_H_ */
