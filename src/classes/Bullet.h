/*
 * Bullet.h
 *
 *  Created on: 05/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_BULLET_H_
#define SRC_CLASSES_BULLET_H_

#include <string>
#include "GameObject.h"
#include "Sprite.h"
#include "Camera.h"

class Bullet : public GameObject {
public:
	Bullet(float x, float y, float angle, float speed, float maxDistance, std::string sprite, float frameCount = 1, float rotation = 0, bool spriteLoop = true);

	void Update(float dt);
	void Render();
	bool IsDead(){ return (distanceLeft <= 0);};
	void NotifyCollision(GameObject* other);

private:
	Sprite sp;
	Point speed;
	float distanceLeft;

};

#endif /* SRC_CLASSES_BULLET_H_ */
