/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <iostream>
#include <SDL2/SDL_opengl.h>


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

	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;

	bool initShaders(void);

private:
	GLuint loadTexture(std::string fileName);
	void printShaderLog(GLuint shader);
	void printProgramLog(GLuint program);


};


#pragma once
#endif
