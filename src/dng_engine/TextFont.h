/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _TEXTFONT_H_
#define _TEXTFONT_H_
#pragma once

#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <SDL_image.h>


typedef struct FontItem {
	short ascii;
	short ucode;
	short top;
	short bottom;
	short x;
	short y;
	short width;
	short height;
	short leading;
	short trailing;

} FontItem;

class TextFont
{
public:
	TextFont(SDL_Renderer* r, std::string fn);
	TextFont(SDL_Renderer* r, std::string fn, bool s);
	~TextFont();

	void draw(const char* text, int x, int y, float size, float scale);

private:
	SDL_Texture* fontImage;
	SDL_Renderer* renderer;
	int imageWidth;
	int imageHeight;
	FontItem** fontItems;
	int charsCount;
	bool scallable;
	
	std::string fontName;

	int fontWidth;
	int fontHeight;
	int fontSpace;

	void parseXML(std::string xmlFileName);
	void prepareImage(SDL_Renderer* r, std::string f);
	float getStringFontWidth(const char* text);

};

#endif
