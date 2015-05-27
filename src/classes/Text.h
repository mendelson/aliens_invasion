/*
 * Text.h
 *
 *  Created on: 24/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_TEXT_H_
#define SRC_CLASSES_TEXT_H_

#include <string>
#include <SDL_ttf.h>

#include "Rect.h"

struct SDL_Texture;

class Text {
public:
	enum TextStyle {
		SOLID, SHADED, BLENDED
	};

	Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x = 0, int y = 0);
	~Text();

	void Render(int cameraX = 0, int cameraY = 0);
	void SetPos(int x, int y, bool centerX = false, bool centerY = false);

	void SetText(std::string text) { this->text = text; RemakeTexture(); }
	void SetColor(SDL_Color color) {this->color = color; RemakeTexture(); }
	void SetStyle(TextStyle style) { this->style = style; RemakeTexture(); };
	void SetFontSize(int fontSize) { this->fontSize = fontSize; RemakeTexture(); };

private:
	void RemakeTexture();

	TTF_Font* font;
	SDL_Texture* texture;

	std::string text;
	TextStyle style;
	int fontSize;
	SDL_Color color;
	Rect box;
};

#endif /* SRC_CLASSES_TEXT_H_ */
