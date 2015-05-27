/*
 * StillAnimation.cpp
 *
 *  Created on: 14/05/2015
 *      Author: MateusMendelson
 */

#include "StillAnimation.h"

#include "Camera.h"

StillAnimation::StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends) : GameObject(STILLANIMATION), sp(sprite), endTimer() {
	this->box.setRect(0, 0, (float) sp.GetFrameWidth(), (float) sp.GetHeight());
	this->box.setCenterAt(x, y);

	this->timeLimit = timeLimit;
	this->oneTimeOnly = ends;
	this->type = STILLANIMATION;
}

void StillAnimation::Update(float dt) {
	sp.Update(dt);
	endTimer.Update(dt);
}

void StillAnimation::Render() {
	this->sp.Render(box.point.x + Camera::pos.x, box.point.y + Camera::pos.y, rotation);
}

bool StillAnimation::IsDead() {
	if (oneTimeOnly) {
		if (endTimer.Get() >= timeLimit) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
