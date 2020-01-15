#include <iostream>
#include <fstream>

#include "Engine.h"
#include "Defines.h"


Engine::Engine() {
	
	if (!readConfigFile()) {
		settings = {
		800,					// Screen width
		600,					// Screen height
		Engine::MIN_SCALE,		// scale
		0,// fullscreen
		20 // music volume
		};
	}	
	
	this->started = false;
	this->quit = false;
	this->window = NULL;
	this->renderer = NULL;
	this->music = NULL;
	this->camera = NULL;
	this->tilesOnScreenFromCenterX = 0;
	this->tilesOnScreenFromCenterY = 0;
	this->coordinatesText[0] = ' ';

	this->mouseRightButtonPressed = false;

	this->viewLockedOn = ViewLockedOn::PLAYER;

	this->scale = settings.scale;

	this->fpsCap = true;
	this->lastTime = 0L;
	this->timer = 0L;
	this->delta = 0.0f;
	this->updates = 0;
	this->frames = 0;
	this->now = 0L;
	this->amountOfTicks = 60.0f;
	this->fpsCount = 0;
	this->ticksCount = 0;
	this->ns = 0;
	this->displayMode = 0;

	this->scrollVector = NULL;

}

Engine::~Engine() {
}

void Engine::initTimer() {
	this->lastTime = SDL_GetTicks();
	this->timer = SDL_GetTicks();
}

void Engine::initSDL() {
	this->started = (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)  == 0);
	if (!this->started) {
		std::cout << "SDL_Init() error : " << SDL_GetError() << std::endl;
		exit(1);
	}
	atexit(SDL_Quit);
	this->started = true;
}

void Engine::createWindow() {
	this->window = SDL_CreateWindow("Dungeon Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (this->window == NULL) {
		std::cout << "SDL_CreateWindow() error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	this->started = true;
}

void Engine::createRenderer() {
	
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer == NULL) {
		std::cout << "SDL_CreateRenderer() error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
	this->started = true;
}

void Engine::initializePngImages() {
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image IMG_Init() error: " << IMG_GetError() << std::endl;
		exit(1);
	}
	this->started = true;
}

void Engine::initializeAudioSystem() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer Mix_OpenAudio() error: " << Mix_GetError() << std::endl;
		exit(1);
	}
	this->started = true;
}

void Engine::stop(void) {
	
	writeConfigFile();

	Mix_FreeMusic(this->music);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	IMG_Quit();
	SDL_Quit();

}

void Engine::launchSubsystems(void) {

	initSDL();
	createWindow();
	createRenderer();
	initializePngImages();
	initializeAudioSystem();

	if (!this->started) {
		std::cout << "Engine could not be started." << std::endl;
		exit(1);
	}

}

bool Engine::loadMusic(const std::string musicFile) {
	std::string musicFileName = DIR_RES_MUSIC + musicFile;
	this->music = Mix_LoadMUS(musicFileName.c_str());
	if (this->music == NULL) {
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

Mix_Music* Engine::getMusic() {
	return this->music;
}

bool Engine::isQuit() {
	return this->quit;
}

void Engine::setQuit(bool q) {
	this->quit = q;
}

SDL_Renderer* Engine::getRenderer() {
	return this->renderer;
}

SDL_Window* Engine::getWindow() {
	return this->window;
}

TextFont* Engine::createFont(std::string fn, bool s) {
	return new TextFont(this->renderer, fn, s);
}

bool Engine::writeConfigFile() {
	this->settings.scale = this->scale;

	std::ofstream ofile(CONFIG_FILE_NAME, std::ios::binary);
	if (!ofile.good()) {
		std::cout << "Cannot open settings file for writing!" << std::endl;
		return false;
	}
	ofile.write((const char*)&this->settings, sizeof(this->settings));
	ofile.close();
	return true;
}

bool Engine::readConfigFile() {
	std::ifstream ifile(CONFIG_FILE_NAME, std::ios::binary);
	if (!ifile.good()) {
		std::cout << "Cannot open settings file for reading!" << std::endl;
		std::cout << "Switching to default values." << std::endl;
		return false;
	}
	ifile.read((char*)&this->settings, sizeof(this->settings));
	ifile.close();
	return true;
}

