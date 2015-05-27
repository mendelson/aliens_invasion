/*
 * Penguins.h
 *
 *  Created on: 12/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_PENGUINS_H_
#define SRC_CLASSES_PENGUINS_H_

#include <stddef.h>

#include "Camera.h"
#include "GameObject.h"
#include "Point.h"
#include "Sprite.h"
#include "Timer.h"

class Penguins : public GameObject {
public:
	Penguins(float x, float y);
	~Penguins();

	void Update(float dt);
	void Render();
	bool IsDead();
	void Shoot();
	void NotifyCollision(GameObject* other);

	static Penguins* player;

private:
	Sprite bodySp;
	Sprite cannonSp;
	Point speed;
	Timer timer;
	float linearSpeed;
	float cannonAngle;
	int hp;
};

#endif /* SRC_CLASSES_PENGUINS_H_ */
