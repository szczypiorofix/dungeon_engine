/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include "TiledMap.h"
#include "Defines.h"
#include "XMLHelper.h"


TiledMap::TiledMap(std::string fileName) {
	
	xmlDocPtr doc;
	xmlNodePtr cur;
	std::string fn = DIR_RES_IMAGES + fileName;

#ifdef _DEBUG
	std::cout << "Parsing tmx file: " << fn << "... " << std::endl;
#endif

	doc = xmlParseFile(fn.c_str());
	if (doc == NULL) {
		std::cout << "Unable to parse document " << fn << std::endl;
		exit(1);
	}
	
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		std::cout << "Empty document" << std::endl;
		exit(1);
	}

	if (xmlStrcmp(cur->name, (const xmlChar*)"map")) {
		std::cout << "Document of wrong type, root node should be 'map' !" << std::endl;
		xmlFreeDoc(doc);
		exit(1);
	}

	this->map = {0,0,0,0,0,0,NULL,0,NULL,0,NULL,0};

	this->map.width			= XMLHelper::readPropInt(cur, (const xmlChar*)"width");
	this->map.height		= XMLHelper::readPropInt(cur, (const xmlChar*)"height");
	this->map.tileWidth		= XMLHelper::readPropInt(cur, (const xmlChar*)"tilewidth");
	this->map.tileHeight	= XMLHelper::readPropInt(cur, (const xmlChar*)"tileheight");

	cur = cur->xmlChildrenNode;
	xmlNodePtr firstForCounter = cur;


	while (firstForCounter != NULL) {
		if ((!xmlStrcmp(firstForCounter->name, (const xmlChar*)"tileset")))		this->map.tileSetCounter++;
		if ((!xmlStrcmp(firstForCounter->name, (const xmlChar*)"layer")))		this->map.layerCounter++;
		if ((!xmlStrcmp(firstForCounter->name, (const xmlChar*)"objectgroup")))	this->map.objectGroupCounter++;
		firstForCounter = firstForCounter->next;
	}

	int tsc = 0;	// tilesets counter
	int lc = 0;		// layers counter
	int ogc = 0;	// object groups counter

	this->map.tileSets		= new TileSet * [this->map.tileSetCounter];
	this->map.layers		= new Layer * [this->map.layerCounter];
	this->map.objectGroups	= new ObjectGroup * [this->map.objectGroupCounter];

	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar*)"tileset"))) {
			this->map.tileSets[tsc] = new TileSet();
			this->map.tileSets[tsc]->firstGid = XMLHelper::readPropInt(cur, (const xmlChar*)"firstgid");
			TileSetSource* tss = this->getTileSetSource((char*)xmlGetProp(cur, (const xmlChar*)"source"));
			this->map.tileSets[tsc]->source = tss;
			tsc++;
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar*)"layer"))) {
			this->map.layers[lc] = new Layer();
			this->map.layers[lc]->id		= XMLHelper::readPropInt(cur, (const xmlChar*)"id");
			this->map.layers[lc]->name		= (char*)xmlGetProp(cur, (const xmlChar*)"name");
			this->map.layers[lc]->width		= XMLHelper::readPropInt(cur, (const xmlChar*)"width");
			this->map.layers[lc]->height	= XMLHelper::readPropInt(cur, (const xmlChar*)"height");
			// this->map.layers[lc]->data = ... parse layer data
			lc++;
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar*)"objectgroup"))) {
			this->map.objectGroups[ogc] = new ObjectGroup();
			this->map.objectGroups[ogc]->id		= XMLHelper::readPropInt(cur, (const xmlChar*)"id");
			this->map.objectGroups[ogc]->name	= (char*)xmlGetProp(cur, (const xmlChar*)"name");
			//this->map.objectGroups[ogc]->objectsCount = ... count objects
			//this->map.objectGroups[ogc]->objects = getTiledObjects...
			ogc++;
		}
		cur = cur->next;
	}

	xmlFreeDoc(doc);
	xmlCleanupMemory();
	xmlCleanupParser();

}

TileSetSource* TiledMap::getTileSetSource(std::string tsxFileName) {
	TileSetSource* tss = new TileSetSource();

	xmlDocPtr tsxDoc;
	xmlNodePtr tsxCurNode;

	std::string fn = DIR_RES_IMAGES + tsxFileName;

#ifdef _DEBUG
	std::cout << "Parsing tsx file: " << fn << "... " << std::endl;
#endif

	tsxDoc = xmlParseFile(fn.c_str());
	if (tsxDoc == NULL) {
		std::cout << "Unable to parse document " << fn << std::endl;
		exit(1);
	}

	tsxCurNode = xmlDocGetRootElement(tsxDoc);
	if (tsxCurNode == NULL) {
		std::cout << "Empty document: " << fn << std::endl;
		xmlFreeDoc(tsxDoc);
		exit(1);
	}

	if (xmlStrcmp(tsxCurNode->name, (const xmlChar*)"tileset")) {
		std::cout << "Document of the wrong type, root node != tileset !!! " << fn << std::endl;
		xmlFreeDoc(tsxDoc);
		exit(1);
	}

	tss->name			= (char*)xmlGetProp(tsxCurNode, (const xmlChar*)"name");
	tss->tileWidth		= XMLHelper::readPropInt(tsxCurNode, (const xmlChar*)"tilewidth");
	tss->tileHeight		= XMLHelper::readPropInt(tsxCurNode, (const xmlChar*)"tileheight");
	tss->tileCount		= XMLHelper::readPropInt(tsxCurNode, (const xmlChar*)"tilecount");
	tss->columns		= XMLHelper::readPropInt(tsxCurNode, (const xmlChar*)"columns");
	
	tsxCurNode = tsxCurNode->xmlChildrenNode;
	while (tsxCurNode != NULL) {
		if ((!xmlStrcmp(tsxCurNode->name, (const xmlChar*)"image"))) {
			tss->imageSource	= (char*)xmlGetProp(tsxCurNode, (const xmlChar*)"source");
			tss->width			= XMLHelper::readPropInt(tsxCurNode, (const xmlChar*)"width");
			tss->height			= XMLHelper::readPropInt(tsxCurNode, (const xmlChar*)"height");
		}
		tsxCurNode = tsxCurNode->next;
	}

	xmlFreeDoc(tsxDoc);
	return tss;
}

int* TiledMap::parseData(xmlDocPtr doc, xmlNodePtr cur) {
	xmlChar* key;
	cur = cur->xmlChildrenNode;
	int* arr = NULL;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar*)"data"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

			//arr = convertDataStringToArray(key);

			unsigned int numbers = 0;
			unsigned int c = 0;
			int cleanCharsNumber = 0;
			// Counting comas
			while (key[c] != '\0') {
				if (key[c] == ',') numbers++;
				// CHECK CR/LF
				if (key[c] != 13 && key[c] != 32 && key[c] != 10) cleanCharsNumber++;
				c++;
			}
			// How many numbers = comas + 1
			numbers++;
			c = 0;

			char* cleanCharsArray{ new char[cleanCharsNumber] {} };
			cleanCharsNumber = 0;
			while (key[c] != '\0') {
				// CHECK CR/LF AND SPACES
				if (key[c] != 13 && key[c] != 32 && key[c] != 10) {
					cleanCharsArray[cleanCharsNumber] = key[c];
					cleanCharsNumber++;
				}
				c++;
			}
			c = 0;
			char delim[] = ",";
			char* ptr = strtok(cleanCharsArray, delim);
			int* numArr = malloc(sizeof(int) * numbers);
			if (numArr == NULL) {
				printf("Malloc 'numArr' error !!!\n");
				exit(1);
			}
			while (ptr != NULL) {
				numArr[c] = stringToInt(ptr);
				ptr = strtok(NULL, delim);
				c++;
			}
			arr = numArr;

			xmlFree(key);
		}
		cur = cur->next;
	}
	return arr;
}

int TiledMap::stringToInt(const char* a) {
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

TiledMap::~TiledMap() {

}

