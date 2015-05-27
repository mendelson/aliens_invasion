/*
 * Text.cpp
 *
 *  Created on: 24/05/2015
 *      Author: MateusMendelson
 */

#include "Text.h"
#include "Resources.h"
#include "Camera.h"
#include <cstdlib>
#include <iostream>

Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x, int y) : box() {
	texture = NULL;

	this->style = style;
	box.point.setPoint(x, y);
	this->fontSize = fontSize;
	this->color = color;
	this->text = text;

	font = Resources::GetFont(fontFile, fontSize);
	RemakeTexture();
}

Text::~Text() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	}
}

void Text::Render(int cameraX, int cameraY) {
	if(texture != NULL) {
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = box.w;
		src.h = box.h;

		SDL_Rect dst;
		dst.x = box.point.x + cameraX;
		dst.y = box.point.y + cameraY;
		dst.w = box.w;
		dst.h = box.h;

		if (SDL_RenderCopy((Game::GetInstance().GetRenderer()), texture, &src, &dst) != 0) {
			cout << "Could not render text properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
			abort();
		}
	}
}

void Text::SetPos(int x, int y, bool centerX, bool centerY) {
	box.point.setPoint(x, y);

	if(centerX) {
		box.point.x = x - ((float) box.w / 2);
	}

	if(centerY) {
		box.point.y = y - ((float) box.h / 2);
	}

}

void Text::RemakeTexture() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	}

	SDL_Surface* surface;

	if (style == SOLID) {
		surface = TTF_RenderText_Solid(font, text.c_str(), color);
	}

	if (style == SHADED) {
		surface = TTF_RenderText_Shaded(font, text.c_str(), color, { 0, 0, 0 });
	}

	if (style == BLENDED) {
		surface = TTF_RenderText_Blended(font, text.c_str(), color);
	}

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

	SDL_FreeSurface(surface);
	int w;
	int h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	box.w = w;
	box.h = h;
}
