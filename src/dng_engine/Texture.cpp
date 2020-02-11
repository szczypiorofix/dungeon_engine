/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include "Defines.h"


Texture::Texture(std::string fileName, GLfloat tileWidth, GLfloat tileHeight) {
	this->id = loadTexture(fileName);
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->columns = (int)(this->width / this->tileWidth);
#ifdef _DEBUG 
	std::cout << "Texture: " << fileName << ", columns: " << this->columns << std::endl;
#endif
	
}


Texture::Texture(std::string fileName) {
	this->id = loadTexture(fileName);
	this->tileWidth = 0.0f;
	this->tileHeight = 0.0f;
	this->columns = 0;
}


GLuint Texture::loadTexture(std::string fileName) {

	SDL_Surface* image = IMG_Load(fileName.c_str());
	if (image == NULL) {
		std::cout << "Unable to load image " << fileName << ", : " << IMG_GetError() << std::endl;
		exit(1);
	}

	this->width = (GLfloat)image->w;
	this->height = (GLfloat)image->h;

	unsigned object(0);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &object);
	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	glDisable(GL_TEXTURE_2D);

	SDL_FreeSurface(image);
	
	return object;
}


Texture::~Texture() {}


void Texture::drawTile(int _id, GLfloat dx, GLfloat dy) {

	if (this->tileWidth > 0 && this->tileHeight > 0) {
		glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->id);

		int sx = (int)( (_id % this->columns) * this->tileWidth );
		int sy = (int)( (_id / this->columns) * this->tileHeight );

		//GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON
		glBegin(GL_QUADS);

			glTexCoord2f( sx / this->width, sy / this->height );
			glVertex2f( dx, dy );

			glTexCoord2f( (sx + this->tileWidth) / this->width, sy / this->height );
			glVertex2f( dx + this->tileWidth, dy );

			glTexCoord2f( (sx + this->tileWidth) / this->width, (sy + this->tileHeight) / this->height );
			glVertex2f( dx + this->tileWidth, dy + this->tileHeight );

			glTexCoord2f( sx / this->width, (sy + this->tileHeight) / this->height );
			glVertex2f( dx, dy + this->tileHeight );

		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

}


void Texture::draw(TextureRect src, TextureRect dest) {
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->id);

	//GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON
	glBegin(GL_QUADS);

		glTexCoord2f( src.x / this->width, src.y / this->height );
		glVertex2f( dest.x, dest.y );

		glTexCoord2f( (src.x + src.w) / this->width , src.y / this->height );
		glVertex2f( dest.x + dest.w, dest.y );

		glTexCoord2f( (src.x + src.w) / this->width, (src.y + src.h) / this->height );
		glVertex2f( dest.x + dest.w, dest.y + dest.h );

		glTexCoord2f( src.x / this->width, (src.y + src.h) / this->height );
		glVertex2f( dest.x, dest.y + dest.h );

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

