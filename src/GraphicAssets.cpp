#include "GraphicAssets.h"
#include "Defines.h"

GraphicAssets* GraphicAssets::getAssets() {
	if (!instance) {
		instance = new GraphicAssets();
	}
	return instance;
}

void GraphicAssets::loadAsset(std::string fileName, SDL_Renderer* renderer, int spriteWidth, int spriteHeight, int imagesEnum) {
	SpriteSheet* tempSpriteSheet = new SpriteSheet(DIR_RES_IMAGES + fileName, renderer, spriteWidth, spriteHeight, imagesEnum);
	GraphicAssets::getAssets()->spriteSheets[imagesEnum] = tempSpriteSheet;
}

GraphicAssets::GraphicAssets() {
	std::cout << "Creating new assets..." << std::endl;
	spriteSheets[0] = NULL;
	spriteSheets[1] = NULL;
}

GraphicAssets::~GraphicAssets() {

}

GraphicAssets* GraphicAssets::instance = nullptr;
