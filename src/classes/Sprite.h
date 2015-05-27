/*
 * Sprite.h
 *
 *  Created on: 25/03/2015
 *      Author: MateusMendelson
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL.h"
#include <string>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::string;
using std::endl;

class Sprite {
public:
	Sprite();
	Sprite(string file, int frameCount = 1, float frameTime= 1, bool loop = true);

	void Open(string file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y, float angle = 0);
	int GetWidth();
	int GetHeight();
	int GetFrameWidth() { return clipRect.w; }
	bool IsOpen();
	void SetScaleX(float scale) { scaleX = scale; };
	void SetScaleY(float scale) { scaleY = scale; };
	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount) { this->frameCount = frameCount;}
	void SetFrameTime(float frameTime) { this->frameTime = frameTime;}

private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	float scaleX;
	float scaleY;
	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
	bool loop;
	bool shouldUpdate;
};

#endif /* SPRITE_H_ */
