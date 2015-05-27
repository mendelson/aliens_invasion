/*
 * GameObject.h
 *
 *  Created on: 06/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_GAMEOBJECT_H_
#define SRC_CLASSES_GAMEOBJECT_H_

#include <string>
#include "Rect.h"

class GameObject {
public:
	enum Type {
		PENGUINS,
		ALIEN,
		MINION,
		PENGUINBULLET,
		MINIONBULLET,
		BULLET,
		STILLANIMATION
	};

	virtual ~GameObject() {}

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual void NotifyCollision(GameObject* other) = 0;
	bool Is(Type t) { return this->type == t; }

	Rect box;
	float rotation;
	Type type;

protected:
	GameObject(Type t) : box(), rotation(0) {this->type = t;}
};

#endif /* SRC_CLASSES_GAMEOBJECT_H_ */
