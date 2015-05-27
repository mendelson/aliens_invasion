/*
 * Sprite.cpp
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#include "Sprite.h"

#include <SDL_error.h>
#include <SDL_render.h>
#include <cmath>
#include "Resources.h"

using namespace std;

Sprite::Sprite() {
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	this->frameCount = 0;
	currentFrame = 0;
	timeElapsed = 0;
	this->frameTime = 0;
	loop = true;
	shouldUpdate = true;
}

Sprite::Sprite(string file, int frameCount, float frameTime, bool loop) {
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	this->frameCount = frameCount;
	currentFrame = 0;
	timeElapsed = 0;
	this->frameTime = frameTime;
	this->loop = loop;
	shouldUpdate = true;
	Open(file);
}

void Sprite::Open(string file) {
	texture = Resources::GetImage(file);

	if(texture == NULL) {
		cout << "Error: could not create texture properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
		abort();
	}

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	if(frameCount == 0)
		frameCount = 1;

	SetClip(0, 0, width/frameCount, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y, float angle) {
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	dst.w = clipRect.w*scaleX;
	dst.h = clipRect.h*scaleY;

	// Converting angle from radians to degrees
	double ang = 360*angle/(2*M_PI);

	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst, ang, NULL, SDL_FLIP_NONE);
}

int Sprite::GetWidth() {
	return width*scaleX;
}

int Sprite::GetHeight() {
	return height*scaleY;
}

bool Sprite::IsOpen() {
	return texture == NULL ? false : true;
}

void Sprite::Update(float dt) {
	if (loop) {
		timeElapsed += dt;

		if (timeElapsed > frameTime) {
			timeElapsed = 0;

			clipRect.x += clipRect.w;

			if (clipRect.x + clipRect.w > width) {
				clipRect.x = 0;
				this->currentFrame = -1;
			}

			this->currentFrame++;
		}
	}
	else {
		timeElapsed += dt;

		if (shouldUpdate) {
			if (timeElapsed > frameTime) {
				timeElapsed = 0;

				clipRect.x += clipRect.w;
				this->currentFrame++;

				if (currentFrame == frameCount) {
					clipRect.x -= clipRect.w;
					shouldUpdate = false;
				}

			}
		}
	}
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame;
	clipRect.x = currentFrame*clipRect.w;
	timeElapsed = 0;
}
