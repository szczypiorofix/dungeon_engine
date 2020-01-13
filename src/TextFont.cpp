#include "TextFont.h"
#include "Defines.h"
#include "XMLHelper.h"


TextFont::TextFont(SDL_Renderer* r, std::string fn) {
	renderer = r;
	charsCount = 0;
	fontWidth = 0;
	fontHeight = 0;
	fontSpace = 0;
	fontName = fn;
	scallable = false;
	fontImage = NULL;
	fontItems = NULL;
	prepareImage(r, fn);
	parseXML(fontName);
}

TextFont::TextFont(SDL_Renderer* r, std::string fn, bool s): TextFont(r, fn) {
	scallable = s;
}

void TextFont::prepareImage(SDL_Renderer* r, std::string f) {
	std::string fileName = DIR_FONTS + f + ".png";
	SDL_Surface* loadedSurface = IMG_Load(fileName.c_str());
	if (loadedSurface == NULL) {
		std::cout << "Unable to load image vingue.png. SDL_image error: " << IMG_GetError() << std::endl;
		exit(1);
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		fontImage = SDL_CreateTextureFromSurface(r, loadedSurface);
		if (fontImage == NULL) {
			std::cout << "Unable to create texture from vingue.png. Error: " << SDL_GetError() << std::endl;
			exit(1);
		}
		else {
			imageWidth = loadedSurface->w;
			imageHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

TextFont::~TextFont() {
}



void TextFont::parseXML(std::string xmlFileName) {

	xmlDocPtr doc;
	xmlNodePtr cur;

	std::string xmlFile = DIR_FONTS + xmlFileName + ".xml";
	doc = xmlParseFile(xmlFile.c_str());
	if (doc == NULL) {
		std::cout << "Document cannot be parsed successfully." << std::endl;
		exit(1);
	}

	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		std::cout << "Empty document." << std::endl;
		exit(1);
	}

	std::cout << "Reading " << xmlFile << " file ..." << std::endl;

	if (xmlStrcmp(cur->name, (const xmlChar*)"font")) {
		std::cout << "Document of the wrong type. Root node must be 'font'." << std::endl;
		xmlFreeDoc(doc);
		exit(1);
	}

	fontWidth = XMLHelper::readPropShort(cur, (const xmlChar*)"width");
	fontHeight = XMLHelper::readPropShort(cur, (const xmlChar*)"height");
	fontSpace = XMLHelper::readPropShort(cur, (const xmlChar*)"space");

	cur = cur->xmlChildrenNode;

	xmlNodePtr mainItems = cur;

	while (mainItems != NULL) {
		if (!xmlStrcmp(mainItems->name, (const xmlChar*)"item")) {
			charsCount++;
		}
		mainItems = mainItems->next;
	}

	fontItems = new FontItem * [charsCount];

	int i = 0;
	mainItems = cur;
	while (mainItems != NULL) {
		if (!xmlStrcmp(mainItems->name, (const xmlChar*)"item")) {
			FontItem* tempItem = new FontItem();
			tempItem->ascii = XMLHelper::readPropShort(mainItems, (const xmlChar*)"ascii");
			tempItem->ucode = XMLHelper::readPropShort(mainItems, (const xmlChar*)"ucode");
			tempItem->top = XMLHelper::readPropShort(mainItems, (const xmlChar*)"top");
			tempItem->bottom = XMLHelper::readPropShort(mainItems, (const xmlChar*)"bottom");
			tempItem->x = XMLHelper::readPropShort(mainItems, (const xmlChar*)"x");
			tempItem->y = XMLHelper::readPropShort(mainItems, (const xmlChar*)"y");
			tempItem->width = XMLHelper::readPropShort(mainItems, (const xmlChar*)"width");
			tempItem->height = XMLHelper::readPropShort(mainItems, (const xmlChar*)"height");
			tempItem->leading = XMLHelper::readPropShort(mainItems, (const xmlChar*)"leading");
			tempItem->trailing = XMLHelper::readPropShort(mainItems, (const xmlChar*)"trailing");
			
			fontItems[i] = tempItem;
			i++;
		}
		mainItems = mainItems->next;
	}

	xmlFreeDoc(doc);
	xmlCleanupMemory();
	xmlCleanupParser();

}

float TextFont::getStringFontWidth(const char* text) {
	float c = 0.0f;
	for (int i = 0; text[i] != 0; i++) {
		for (int j = 0; j < charsCount; j++) {
			if (text[i] == fontItems[j]->ascii) {
				c += fontItems[j]->width;
			}
		}
	}
	std::cout << c << std::endl;
	return c;
}

void TextFont::draw(const char* text, int x, int y, float size, float scale) {
	SDL_Rect renderQuad = { 0, 0, 0, 0 };
	int c = 0;
	while (text[c] != 0) {
		for (int i = 0; i < charsCount; i++) {
			if (text[c] == fontItems[i]->ascii) {
				
				renderQuad.x = x + fontItems[i]->trailing + fontItems[i]->leading + (int)(c * fontWidth * size);
				renderQuad.y = y + fontHeight + fontItems[i]->top;
				renderQuad.w = (int) (fontWidth * scale * size);
				renderQuad.h = (int) (fontHeight * scale * size);
				
				SDL_Rect clip = { fontItems[i]->x, fontItems[i]->y, fontItems[i]->width, fontItems[i]->height };
				SDL_RenderCopy(renderer, fontImage, &clip, &renderQuad);
			}
		}
		c++;
	}
	
}

