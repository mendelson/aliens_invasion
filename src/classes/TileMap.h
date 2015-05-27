/*
 * TileMap.h
 *
 *  Created on: 08/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_TILEMAP_H_
#define SRC_CLASSES_TILEMAP_H_

#include "TileSet.h"
#include "Camera.h"
#include <iostream>
#include <cstdio>
#include <vector>

class TileMap {
public:
	TileMap(std::string, TileSet*);

	void Load(std::string);
	void SetTileSet(TileSet*);
	int& At(int, int, int z = 0);
	void Render(int cameraX = 0, int cameraY = 0);
	void RenderLayer (int, int cameraX = 0, int cameraY = 0);
	int GetWidth() { return mapWidth; }
	int GetHeight(){ return mapHeight; }
	int GetDepth(){ return mapDepth; }

private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};

#endif /* SRC_CLASSES_TILEMAP_H_ */
