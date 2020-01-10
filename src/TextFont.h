#ifndef _TEXTFONT_H_
#define _TEXTFONT_H_
#pragma once

#include <iostream>
#include <libxml/parser.h>
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
	TextFont(SDL_Renderer* renderer, std::string fontName);
	~TextFont();

private:
	SDL_Texture* fontImage;
	int imageWidth;
	int imageHeight;
	FontItem** fontItems;
	int charsCount;
	
	int fontWidth;
	int fontHeight;
	int fontSpace;

	int xmlCharToInt(const xmlChar a[]);
	short xmlCharToShort(const xmlChar a[]);
	void parseXML(std::string xmlFileName);
	short readPropShort(xmlNodePtr node, const xmlChar* prop);

};

#endif
