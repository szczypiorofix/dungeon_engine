#include "TextFont.h"
#include "Defines.h"



TextFont::TextFont(SDL_Renderer* renderer, std::string fontName) {
	charsCount = 0;
	fontWidth = 0;
	fontHeight = 0;
	fontSpace = 0;

	fontImage = NULL;
	std::string fileName = DIR_FONTS + fontName + ".png";
	SDL_Surface* loadedSurface = IMG_Load(fileName.c_str());
	if (loadedSurface == NULL) {
		std::cout << "Unable to load image vingue.png. SDL_image error: " << IMG_GetError() << std::endl;
		exit(1);
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		fontImage = SDL_CreateTextureFromSurface(renderer, loadedSurface);
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

	fontItems = NULL;
	parseXML(fontName);
}

TextFont::~TextFont() {
}

int TextFont::xmlCharToInt(const xmlChar a[]) {
	int c = 0, sign = 0, offset = 0, n = 0;
	if (a[0] == '-') {
		sign = -1;
	}
	if (sign == -1) {
		offset = 1;
	}
	else {
		offset = 0;
	}
	n = 0;
	for (c = offset; a[c] != '\0'; c++) {
		n = n * 10 + a[c] - '0';
	}
	if (sign == -1) {
		n = -n;
	}
	return n;
}

short TextFont::xmlCharToShort(const xmlChar a[]) {
	short c = 0, sign = 0, offset = 0, n = 0;
	if (a[0] == '-') {
		sign = -1;
	}
	if (sign == -1) {
		offset = 1;
	}
	else {
		offset = 0;
	}
	n = 0;
	for (c = offset; a[c] != '\0'; c++) {
		n = n * 10 + a[c] - '0';
	}
	if (sign == -1) {
		n = -n;
	}
	return n;
}

short TextFont::readPropShort(xmlNodePtr node, const xmlChar* prop) {
	return xmlGetProp(node, prop) != NULL ? xmlCharToShort(xmlGetProp(node, prop)) : 0;
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

	fontWidth = xmlCharToInt(xmlGetProp( cur, (const xmlChar *) "width" ));
	fontHeight = xmlCharToInt(xmlGetProp(cur, (const xmlChar*)"height"));
	fontSpace = xmlCharToInt(xmlGetProp(cur, (const xmlChar*)"space"));

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
			tempItem->ascii = readPropShort(mainItems, (const xmlChar*)"ascii");
			tempItem->ucode = readPropShort(mainItems, (const xmlChar*)"ucode");
			tempItem->top = readPropShort(mainItems, (const xmlChar*)"top");
			tempItem->bottom = readPropShort(mainItems, (const xmlChar*)"bottom");
			tempItem->x = readPropShort(mainItems, (const xmlChar*)"x");
			tempItem->y = readPropShort(mainItems, (const xmlChar*)"y");
			tempItem->width = readPropShort(mainItems, (const xmlChar*)"width");
			tempItem->height = readPropShort(mainItems, (const xmlChar*)"height");
			tempItem->leading = readPropShort(mainItems, (const xmlChar*)"leading");
			tempItem->trailing = readPropShort(mainItems, (const xmlChar*)"trailing");
			
			fontItems[i] = tempItem;
			i++;
		}
		mainItems = mainItems->next;
	}

	std::cout << "Chars count: " << charsCount << std::endl;

	xmlFreeDoc(doc);
	xmlCleanupMemory();
	xmlCleanupParser();

}
