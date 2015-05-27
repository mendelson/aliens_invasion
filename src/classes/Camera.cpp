/*
 * Camera.cpp
 *
 *  Created on: 22/04/2015
 *      Author: MateusMendelson
 */

#include "Camera.h"

Point Camera::pos;
Point Camera::speed;
GameObject* Camera::focus;

void Camera::Update(float dt) {
	float x = 0;
	float y = 0;

	// In this case, there is no focus, so dt is considered
	if (focus == NULL) {
		if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
			// New position
			y = pos.y - ARROW_CONSTANT*dt;

			// New speed
			speed.setPoint(0, (y - pos.y) / 2);

			// New old position
			pos.y = y;
		}
		if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
			// New position
			x = pos.x - ARROW_CONSTANT*dt;

			// New speed
			speed.setPoint((x - pos.x) / 2, 0);

			// New old position
			pos.x = x;
		}
		if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
			// New position
			y = pos.y + ARROW_CONSTANT*dt;

			// New speed
			speed.setPoint(0, (y - pos.y) / 2);

			// New old position
			pos.y = y;
		}
		if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
			// New position
			x = pos.x + ARROW_CONSTANT*dt;

			// New speed
			speed.setPoint((x - pos.x) / 2, 0);

			// New old position
			pos.x = x;
		}
	}
	// centralizar o foco na tela. Nesse caso, o movimento independe de dt
	else {
		//x = focus->

		pos.setPoint(- focus->box.getCenter().x + 512, - focus->box.getCenter().y + 300);
	}
}
