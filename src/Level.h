#ifndef _LEVEL_H_
#define _LEVEL_H_
#pragma once

#include <iostream>

typedef struct ObjectGroup {
	int id;
	std::string name;
} ObjectGroup;

typedef struct TileSet {
	int firstId;
	std::string source;
} TileSet;

typedef struct Layer {
	int id;
	std::string name;
	int width;
	int height;
	int* data[];
} Layer;

typedef struct Map {
	
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int nextLayerId;
	int nextObjectId;

} Map;


class Level {

public:
	Level();
	~Level();

private:


};

#endif
