/*
 * Minion.h
 *
 *  Created on: 05/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_MINION_H_
#define SRC_CLASSES_MINION_H_

#include "GameObject.h"
#include "Rect.h"
#include "Sprite.h"
#include "Bullet.h"
#include "StillAnimation.h"
#include "Game.h"
#include <vector>

class Minion : public GameObject {
public:
	Minion(GameObject* minionCenter, float arcOffset = 0, float scaleX = 1, float scaleY = 1);

	void Update (float dt);
	void Render();
	bool IsDead();
	void Shoot(Point pos);
	void NotifyCollision(GameObject* other) {};
	void Kill() { this->dead = true; }

private:
	GameObject* center;
	Sprite sp;
	float arc;
	bool dead;
};

#endif /* SRC_CLASSES_MINION_H_ */
