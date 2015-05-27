/*
 * Bullet.cpp
 *
 *  Created on: 05/05/2015
 *      Author: MateusMendelson
 */

#include "Bullet.h"

#include <cmath>
#include <iostream>

#include "Point.h"

Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, std::string sprite, float frameCount, float rotation, bool spriteLoop) : GameObject(BULLET), sp(sprite.c_str(), frameCount, 0.2, spriteLoop), speed()  {
	this->rotation = rotation;

	this->box.setRect(0, 0, (float) sp.GetFrameWidth(), (float) sp.GetHeight());
	this->box.setCenterAt(x, y);

	this->speed.setPoint(speed * cos(angle), speed * sin(angle));

	this->distanceLeft = maxDistance;

	if (sprite.find("minion") != std::string::npos) {
		this->type = MINIONBULLET;
	} else if (sprite.find("penguin") != std::string::npos) {
		this->type = PENGUINBULLET;
	}
}

void Bullet::Update(float dt) {
	this->distanceLeft -= this->speed.getMagnitude() * dt;

	this->box.setCenterAt(this->box.getCenter().x + this->speed.x * dt, this->box.getCenter().y + this->speed.y * dt);

	this->sp.Update(dt);
}

void Bullet::Render() {
	this->sp.Render(box.point.x + Camera::pos.x, box.point.y + Camera::pos.y, rotation);
}

void Bullet::NotifyCollision(GameObject* other) {
	if (this->type == MINIONBULLET || this->type == BULLET) {
		if (other->Is(PENGUINS)) {
			this->distanceLeft = 0;
		}
	}
	if (this->type == PENGUINBULLET || this->type == BULLET) {
		if (other->Is(ALIEN)) {
			this->distanceLeft = 0;
		}
	}
}
