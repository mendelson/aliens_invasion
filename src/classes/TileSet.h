/*
 * TileSet.h
 *
 *  Created on: 08/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_TILESET_H_
#define SRC_CLASSES_TILESET_H_

#include "Sprite.h"
#include <iostream>

class TileSet {
public:
	TileSet(int, int, std::string);

	void Render(unsigned index, float x, float y);
	int GetTileWidth() { return tileWidth; }
	int GetTileHeight() { return tileHeight; }

private:
	Sprite tileSet;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;
};

#endif /* SRC_CLASSES_TILESET_H_ */
