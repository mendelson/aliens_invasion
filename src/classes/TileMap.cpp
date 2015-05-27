/*
 * TileMap.cpp
 *
 *  Created on: 08/04/2015
 *      Author: MateusMendelson
 */

#include "TileMap.h"

TileMap::TileMap(std::string file, TileSet* tileSet) {
	Load(file);
	SetTileSet(tileSet);
}

void TileMap::Load(std::string file) {
	int temp;
	char trash;
	FILE* input = std::fopen(file.c_str(), "r");

	if (input == NULL) {
		std::cout << "Could not open '" << file << "'.\nAborting ..." << std::endl;
		abort();
	}

	// Reading width, height and depth
	fscanf(input, "%d", &mapWidth);
	fscanf(input, "%c", &trash);
	fscanf(input, "%d", &mapHeight);
	fscanf(input, "%c", &trash);
	fscanf(input, "%d", &mapDepth);
	fscanf(input, "%c", &trash);

	int mapSize = mapWidth*mapHeight*mapDepth;

	for(int i = 0; i < mapSize; i++) {
		fscanf(input, "%d", &temp);
		tileMatrix.emplace_back(--temp);
		fscanf(input, "%c", &trash);
	}

	fclose(input);
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
	return tileMatrix[x + y*mapWidth + z*mapWidth*mapHeight];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
	int valueOnMap;

	cameraX = cameraX + (0.4*layer)*cameraX;
	cameraY = cameraY + (0.4*layer)*cameraY;

	for(int y = 0; y < mapHeight; y++){
		for(int x = 0; x < mapWidth; x++){
			valueOnMap = At(x, y, layer);
			if(valueOnMap >= 0){
				tileSet->Render(valueOnMap, x*tileSet->GetTileWidth() + cameraX, y*tileSet->GetTileHeight() + cameraY);
			}
		}
	}
}

void TileMap::Render(int cameraX, int cameraY) {
	for (int i = 0; i < mapDepth; i++) {
		this->RenderLayer(i, cameraX, cameraY);
	}
}
