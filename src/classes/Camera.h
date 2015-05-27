/*
 * Camera.h
 *
 *  Created on: 22/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_CAMERA_H_
#define SRC_CLASSES_CAMERA_H_

#include "Point.h"
#include "GameObject.h"
#include "InputManager.h"
#include <cstdio>

const int ARROW_CONSTANT = 800;

class Camera {
public:
	static void Follow(GameObject* newFocus) { focus = newFocus; }
	static void Unfollow() { focus = NULL; }
	static void Update(float dt);

	static Point pos;
	static Point speed;

private:
	static GameObject* focus;
};

#endif /* SRC_CLASSES_CAMERA_H_ */
