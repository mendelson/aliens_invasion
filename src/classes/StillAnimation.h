/*
 * StillAnimation.h
 *
 *  Created on: 14/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_STILLANIMATION_H_
#define SRC_CLASSES_STILLANIMATION_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class StillAnimation : public GameObject {
public:
	StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends);

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject* other) {};

private:
	Sprite sp;
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
};

#endif /* SRC_CLASSES_STILLANIMATION_H_ */
