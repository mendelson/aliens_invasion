/*
 * Minion.cpp
 *
 *  Created on: 05/05/2015
 *      Author: MateusMendelson
 */

#include "Minion.h"

#include <SDL_stdinc.h>
#include <cmath>

#include "Camera.h"
#include "Game.h"
#include "Point.h"
#include "State.h"

const float r = 150;
const float w = M_PI/3;
const float bulletSpeed = 700;
const float bulletMaxDistance = 2000;

Minion::Minion(GameObject* minionCenter, float arcOffset, float scaleX, float scaleY) : GameObject(MINION), sp("img/minion.png") {
	sp.SetScaleX(scaleX);
	sp.SetScaleY(scaleY);

	this->center = minionCenter;
	this->arc = arcOffset;

	this->box.setRect(0, 0, (float) sp.GetWidth(), (float) sp.GetHeight());
	this->box.setCenterAt(center->box.getCenter().x + r * cos(arc), center->box.getCenter().y + r * sin(arc));

	dead = false;
}

void Minion::Update(float dt) {
	if (!dead) {
		arc += w * dt;
		rotation = arc + (M_PI / 2);
		this->box.setCenterAt(center->box.getCenter().x + r * cos(arc), center->box.getCenter().y + r * sin(arc));
	}
}

void Minion::Render() {
	this->sp.Render(box.point.x + Camera::pos.x, box.point.y + Camera::pos.y, rotation);
}

void Minion::Shoot(Point pos) {
	float angle = box.getCenter().getAngleOfInclination(pos);

	if(pos.x < box.getCenter().x) {
		angle += M_PI;
	}

	Bullet* bullet = new Bullet(box.getCenter().x, box.getCenter().y, angle, bulletSpeed, bulletMaxDistance, "img/minionbullet2.png", 3, angle);

	Game::GetInstance().GetCurrentState().AddObject(bullet);
}

bool Minion::IsDead() {
	if (dead) {
		int frames = 4;
		float frameTime = 0.1;
		float timeLimit = frames * frameTime;

		StillAnimation* death = new StillAnimation(this->box.getCenter().x, this->box.getCenter().y, this->rotation, Sprite("img/miniondeath.png", frames, frameTime, false), timeLimit, true);

		Game::GetInstance().GetCurrentState().AddObject(death);

		return true;
	}

	return false;
}
