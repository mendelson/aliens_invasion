/*
 * Penguins.cpp
 *
 *  Created on: 12/05/2015
 *      Author: MateusMendelson
 */

#include "Penguins.h"

#include <SDL_keycode.h>
#include <SDL_stdinc.h>
#include <cmath>
#include <cstdlib>

#include "Bullet.h"
#include "Game.h"
#include "InputManager.h"
#include "State.h"
#include "StillAnimation.h"
#include "Sound.h"

const int a = 500;
const int stopA = 400;
const int maxSpeed = 600;
const float angSpeed = M_PI;
const float bulletSpeed = 700;
const float bulletMaxDistance = 2000;
const int distanceFromCenter = 65;
const float cooldown = 0.3;

Penguins* Penguins::player;

Penguins::Penguins(float x, float y) : GameObject(PENGUINS), bodySp("img/penguin.png"), cannonSp("img/cubngun.png"), speed(), timer() {
	this->box.setRect(0, 0, (float) bodySp.GetFrameWidth(), (float) bodySp.GetHeight());
	this->box.setCenterAt(x, y);

	hp = 50;
	linearSpeed = 0;
	cannonAngle = 0;

	player = this;
}

Penguins::~Penguins() {
	player = NULL;
}

void Penguins::Update(float dt) {
	timer.Update(dt);

	linearSpeed = speed.getMagnitude();

	if(!speed.direction) {
		linearSpeed = -linearSpeed;
	}

	if(!(InputManager::GetInstance().IsKeyDown(SDLK_w)) && !(InputManager::GetInstance().IsKeyDown(SDLK_s))) {
		if(linearSpeed <= stopA/10 && linearSpeed >= -stopA/10) {
			speed.setPoint(0, 0);
		}
		else if(linearSpeed > 0) {
			linearSpeed -= stopA * dt;

			speed.x = linearSpeed * cos(rotation);
			speed.y = linearSpeed * sin(rotation);
		}
		else if(linearSpeed < 0) {
			linearSpeed += stopA * dt;

			speed.x = linearSpeed * cos(rotation);
			speed.y = linearSpeed * sin(rotation);
		}

		box.point.x += speed.x * dt;
		box.point.y += speed.y * dt;
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_w)) {
		linearSpeed += a * dt;

		if(linearSpeed >= 0) {
			speed.direction = true;
		}
		else {
			speed.direction = false;
		}

		if(linearSpeed > maxSpeed) {
			linearSpeed = maxSpeed;
		}

		speed.x = linearSpeed * cos(rotation);
		speed.y = linearSpeed * sin(rotation);

		box.point.x += speed.x * dt;
		box.point.y += speed.y * dt;
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_s)) {
		linearSpeed -= a * dt;

		if (linearSpeed >= 0) {
			speed.direction = true;
		} else {
			speed.direction = false;
		}

		if (linearSpeed < -maxSpeed) {
			linearSpeed = -maxSpeed;
		}

		speed.x = linearSpeed * cos(rotation);
		speed.y = linearSpeed * sin(rotation);

		box.point.x += speed.x * dt;
		box.point.y += speed.y * dt;
	}

	if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
		this->rotation -= angSpeed * dt;
	}

	if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
		this->rotation += angSpeed * dt;
	}

	// Checking map's boundaries
	if (box.point.x > 1408) {
		box.point.x = 1408;
		speed.x = 0;
	}

	if (box.point.x < 0){
		box.point.x = 0;
		speed.x = 0;
	}

	if (box.point.y > 1280){
		box.point.y = 1280;
		speed.y = 0;
	}

	if (box.point.y < 0){
		box.point.y = 0;
		speed.y = 0;
	}

	Point mouse(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y);

	cannonAngle = box.getCenter().getAngleOfInclination(mouse);

	if (mouse.x < box.getCenter().x) {
		cannonAngle += M_PI;
	}

	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		Shoot();
	}
}

void Penguins::Render() {
	this->bodySp.Render(box.point.x + Camera::pos.x, box.point.y + Camera::pos.y, rotation);

	this->cannonSp.Render(box.getCenter().x - ((float) cannonSp.GetFrameWidth()/ 2 ) + Camera::pos.x, box.getCenter().y - ((float) cannonSp.GetHeight()/ 2 ) + Camera::pos.y, cannonAngle);
}

void Penguins::Shoot() {
	if (timer.Get() > cooldown) {
		Bullet* bullet = new Bullet(box.getCenter().x + distanceFromCenter * cos(cannonAngle), box.getCenter().y + distanceFromCenter * sin(cannonAngle), cannonAngle, bulletSpeed, bulletMaxDistance, "img/penguinbullet.png", 4, cannonAngle, false);

		Game::GetInstance().GetCurrentState().AddObject(bullet);

		timer.Restart();
	}
}

void Penguins::NotifyCollision(GameObject* other) {
	if (other->Is(MINIONBULLET)) {
		this->hp -= rand() % 10 + 10;
	} else if (other->Is(MINION) || other->Is(ALIEN)) {
		hp = 0;
	}
}

bool Penguins::IsDead() {
	if (hp <= 0) {
		player = NULL;
		Camera::Unfollow();

		int frames = 5;
		float frameTime = 0.1;
		float timeLimit = frames * frameTime;

		StillAnimation* death = new StillAnimation(this->box.getCenter().x, this->box.getCenter().y, this->rotation, Sprite("img/penguindeath.png", frames, frameTime, false), timeLimit, true);

		Game::GetInstance().GetCurrentState().AddObject(death);

		// Death sound
		Sound* s = new Sound("audio/boom.wav");
		s->Play(0);

		return true;
	}

	return false;
}
