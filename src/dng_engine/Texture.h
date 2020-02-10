/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <iostream>
#include <SDL_opengl.h>


typedef struct TextureRect {
	GLfloat x, y;
	GLfloat w, h;
} TextureRect;



class Texture {

public:
	Texture(std::string fileName);
	Texture(std::string fileName, GLfloat tileWidth, GLfloat tileHeight);
	~Texture();

	GLuint id;

	GLfloat width;
	GLfloat height;
	GLfloat tileWidth;
	GLfloat tileHeight;
	int columns;

	void draw(TextureRect src, TextureRect dest);
	void drawTile(int _id, GLfloat dx, GLfloat dy);


private:
	GLuint loadTexture(std::string fileName);


};


#pragma once
#endif
