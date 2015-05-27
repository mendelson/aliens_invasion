/*
 * State.cpp
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#include "State.h"

#include "Collision.h"
#include "Game.h"

State::State() {
	popRequested = false;
	quitRequested = false;
}
State::~State() {
	objectArray.clear();
}

void State::AddObject(GameObject* ptr) {
	objectArray.emplace_back(ptr);
}

void State::UpdateArray(float dt) {
	// Updating objects
	for (int i = objectArray.size() - 1; i >= 0; --i) {
		objectArray[i]->Update(Game::GetDeltaTime());
	}

	// Checking for collisions
	for (int i = objectArray.size() - 1; i >= 0; --i) {
		for (int j = 0; j < i; ++j) {
			if(Collision::IsColliding(objectArray[i]->box, objectArray[j]->box, objectArray[i]->rotation, objectArray[j]->rotation)) {
				objectArray[i]->NotifyCollision(objectArray[j].get());
				objectArray[j]->NotifyCollision(objectArray[i].get());
			}
		}
	}

	// Looking for dead objects and removing them
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i); // deleting the i-th element
			i--;
		}
	}
}

void State::RenderArray() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}
