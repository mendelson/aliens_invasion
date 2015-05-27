/*
 * TileSet.cpp
 *
 *  Created on: 08/04/2015
 *      Author: MateusMendelson
 */

#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : tileSet(file) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	if(!tileSet.IsOpen()) {
		cout << "Error: could not open tileset.png properly. SDL_GetError returned the following: " << SDL_GetError() << endl << "Aborting..." << endl;
		abort();
	}

	rows = tileSet.GetHeight()/tileHeight;
	columns = tileSet.GetWidth()/tileWidth;
}

void TileSet::Render (unsigned index, float x, float y) {
	// Checking index
	if(index > (unsigned) rows*columns - 1) {
		std::cout << "Error: invalid index for TileSet::Render\nAborting ..." << std::endl;
		abort();
	}

	// Calculate clip
	int clipY = (int) index/columns;
	int clipX = (int) index%columns;

	tileSet.SetClip(clipX*tileWidth, clipY*tileHeight, tileWidth, tileHeight);
	tileSet.Render(x, y);
}
