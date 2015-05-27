/*
 * Alien.h
 *
 *  Created on: 24/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_ALIEN_H_
#define SRC_CLASSES_ALIEN_H_

#include <queue>
#include <vector>

#include "GameObject.h"
#include "Minion.h"
#include "Rect.h"
#include "Sprite.h"
#include "Timer.h"

class Alien: public GameObject {
public:
	Alien(float x, float y, int nMinions);
	~Alien(){ alienCount--; minionArray.clear(); }

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject* other);

	static int alienCount;

private:
	class Action {
		public:
			enum ActionType {
				MOVE,
				SHOOT
			};

			Action(ActionType type, float x, float y, int minion) : pos(x, y), evaluated(false) { this->type = type; this->minion = minion; }
			ActionType getType() { return type; }

			ActionType type;
			Point pos;
			bool evaluated;
			int minion;
	};

	enum AlienState {
		MOVING,
		RESTING
	};

	Sprite sp;
	Point speed;
	int hp;
	AlienState alienState;
	Timer shootCooldown;

	std::queue<Action> taskQueue;
	std::vector<Minion> minionArray;
};

#endif /* SRC_CLASSES_ALIEN_H_ */
