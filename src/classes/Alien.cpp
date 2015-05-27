/*
 * Alien.cpp
 *
 *  Created on: 24/04/2015
 *      Author: MateusMendelson
 */

#include "Alien.h"

#include <SDL_stdinc.h>
#include <cmath>
#include <cstdlib>

#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "State.h"
#include "StillAnimation.h"
#include "Sound.h"

const int speedConstant = 100;
const int minDistance = speedConstant/10;
static float theta1;
static float theta2;
const float angularSpeed = -M_PI/5;
const float cooldown = 0.5;
const float distanceToShoot = 400;

int Alien::alienCount = 0;

Alien::Alien(float x, float y, int nMinions) : GameObject(ALIEN), sp("img/alien.png"), speed(), hp(30), shootCooldown() {
	alienCount++;
	alienState = RESTING;

	box.setRect(0, 0, (float) sp.GetWidth(), (float) sp.GetHeight());
	box.setCenterAt(x, y);

	// Populating minion's array
	for(int i = 0; i < nMinions; i++) {

		float scale = rand() % 6;

		scale = scale/10;
		scale += 1;

		float angle = (float) i*(2*M_PI/nMinions);

		minionArray.emplace_back(this, angle, scale, scale);
	}
}

void Alien::Update(float dt) {
	// Updating rotation
	rotation += angularSpeed*dt;

	// Checking if the player has already been defeated
	if (Penguins::player != NULL) {
		// Checking current state
		if (alienState == RESTING) {
			shootCooldown.Update(dt);

			if (shootCooldown.Get() > cooldown) {
				taskQueue.emplace(Action::MOVE, Penguins::player->box.getCenter().x, Penguins::player->box.getCenter().y, -1);
				alienState = MOVING;
			}
		}

		// Evaluating queue
		if (!taskQueue.empty()) {
			if (taskQueue.front().getType() == Action::SHOOT) {
				minionArray[taskQueue.front().minion].Shoot(taskQueue.front().pos);

				taskQueue.pop();
			} else if (taskQueue.front().getType() == Action::MOVE) {
				float dx = taskQueue.front().pos.x - box.getCenter().x;
				float dy = taskQueue.front().pos.y - box.getCenter().y;
				float distance = sqrt(dx * dx + dy * dy);

				if (!taskQueue.front().evaluated) {
					theta1 = acos(dx / distance);
					theta2 = asin(dy / distance);
					this->speed.setPoint(speedConstant * cos(theta1), speedConstant * sin(theta2));

					taskQueue.front().evaluated = true;
				}

				if (distance < distanceToShoot + minDistance) {
					// Shooting
					int minion = 0;
					int min = 100000;
					int minTemp = 0;

					Point p((float) Penguins::player->box.getCenter().x, Penguins::player->box.getCenter().y);

					for (unsigned int i = 0; i < minionArray.size(); i++) {
						Point p2(minionArray[i].box.getCenter().x - Camera::pos.x, minionArray[i].box.getCenter().y - Camera::pos.y);
						if ((minTemp = p2.getDistanceFrom(p)) < min) {
							min = minTemp;
							minion = i;
						}
					}

					taskQueue.emplace(Action::SHOOT, Penguins::player->box.getCenter().x, Penguins::player->box.getCenter().y, minion);

					// Retira a ação da fila
					taskQueue.pop();

					shootCooldown.Restart();

					alienState = RESTING;
				} else {
					float dX = this->speed.x * dt;
					float dY = this->speed.y * dt;

					box.point.x += dX;
					box.point.y += dY;
				}
			}
		}
	}

	// Updating Minions
	for (unsigned int i = 0; i < minionArray.size(); i++) {
		minionArray[i].Update(dt);
	}
}

void Alien::Render() {
	// Rendering Alien
	this->sp.Render(box.point.x + Camera::pos.x, box.point.y + Camera::pos.y, rotation);

	// Rendering Minions
	for(unsigned int i = 0; i < minionArray.size(); i++) {
		minionArray[i].Render();
	}
}

void Alien::NotifyCollision(GameObject* other) {
	if(other->Is(PENGUINBULLET)) {
		this->hp -= rand() % 10 + 10;
	}
}

bool Alien::IsDead() {
	if (hp <= 0) {
		for(unsigned int i = 0; i < minionArray.size(); i++) {
			minionArray[i].Kill();
			minionArray[i].IsDead();
		}

		minionArray.clear();

		int frames = 4;
		float frameTime = 0.1;
		float timeLimit = frames * frameTime;

		StillAnimation* death = new StillAnimation(this->box.getCenter().x, this->box.getCenter().y, this->rotation, Sprite("img/aliendeath.png", frames, frameTime, false), timeLimit, true);

		Game::GetInstance().GetCurrentState().AddObject(death);

		// Death sound
		Sound* s = new Sound("audio/boom.wav");
		s->Play(0);

		return true;
	}

	return false;
}
