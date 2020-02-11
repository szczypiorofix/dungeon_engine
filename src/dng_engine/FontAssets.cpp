#include "FontAssets.h"



FontAssets::FontAssets() {
	std::cout << "Creating new font assets..." << std::endl;
	this->fonts[0] = NULL;
}


FontAssets::~FontAssets() {}


void FontAssets::releaseAssets() {
	std::cout << "Releasing textures... ";
	for (int i = 0; i < MAX_FONTS; i++) {
		delete FontAssets::getAssets()->fonts[i];
	}
	std::cout << "done." << std::endl;
}


FontAssets* FontAssets::getAssets() {
	if (!instance) {
		instance = new FontAssets();
	}
	return instance;
}


void FontAssets::addToAssets(std::string fileName, Texture* tex, const int fontEnum) {
	TextFont* tempFont = new TextFont(fileName, tex);
	FontAssets::getAssets()->fonts[fontEnum] = tempFont;
}



FontAssets* FontAssets::instance = nullptr;

