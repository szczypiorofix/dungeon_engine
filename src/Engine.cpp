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
	
	mStarted = false;
	mQuit = false;
	mWindow = NULL;
	mRenderer = NULL;
	mMusic = NULL;
	mCamera = NULL;
	mTilesOnScreenFromCenterX = 0;
	mTilesOnScreenFromCenterY = 0;
	mCoordinatesText[0] = ' ';

	mMouseRightButtonPressed = false;

	mViewLockedOn = ViewLockedOn::PLAYER;

	this->scale = settings.scale;

	mFpsCap = true;
	mLastTime = 0L;
	mTimer = 0L;
	mDelta = 0.0f;
	mUpdates = 0;
	mFrames = 0;
	mNow = 0L;
	mAmountOfTicks = 60.0f;
	mFpsCount = 0;
	mTicksCount = 0;
	mNs = 0;
	mDisplayMode = 0;

	mScrollVector = NULL;

}

Engine::~Engine() {
}

void Engine::initTimer() {
	mLastTime = SDL_GetTicks();
	mTimer = SDL_GetTicks();
}

void Engine::initSDL() {
	mStarted = (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)  == 0);
	if (!mStarted) {
		std::cout << "SDL_Init() error : " << SDL_GetError() << std::endl;
		exit(1);
	}
	atexit(SDL_Quit);
	mStarted = true;
}

void Engine::createWindow() {
	mWindow = SDL_CreateWindow("Dungeon Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mWindow == NULL) {
		std::cout << "SDL_CreateWindow() error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	mStarted = true;
}

void Engine::createRenderer() {
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == NULL) {
		std::cout << "SDL_CreateRenderer() error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
	mStarted = true;
}

void Engine::initializePngImages() {
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image IMG_Init() error: " << IMG_GetError() << std::endl;
		exit(1);
	}
	mStarted = true;
}

void Engine::initializeAudioSystem() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer Mix_OpenAudio() error: " << Mix_GetError() << std::endl;
		exit(1);
	}
	mStarted = true;
}

void Engine::stop(void) {
	
	writeConfigFile();

	Mix_FreeMusic(mMusic);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	IMG_Quit();
	SDL_Quit();

}

void Engine::launchSubsystems(void) {

	initSDL();
	createWindow();
	createRenderer();
	initializePngImages();
	initializeAudioSystem();

	if (!mStarted) {
		std::cout << "Engine could not be started." << std::endl;
		exit(1);
	}

}

bool Engine::loadMusic(const std::string musicFile) {
	std::string musicFileName = DIR_RES_MUSIC + musicFile;
	mMusic = Mix_LoadMUS(musicFileName.c_str());
	if (mMusic == NULL) {
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

Mix_Music* Engine::getMusic()
{
	return mMusic;
}

bool Engine::isQuit() {
	return mQuit;
}

void Engine::setQuit(bool quit) {
	mQuit = quit;
}

SDL_Renderer* Engine::getRenderer() {
	return mRenderer;
}

SDL_Window* Engine::getWindow() {
	return mWindow;
}

TextFont* Engine::createFont(std::string fn, bool s) {
	return new TextFont(mRenderer, fn, s);
}

bool Engine::writeConfigFile() {
	settings.scale = scale;

	std::ofstream ofile(CONFIG_FILE_NAME, std::ios::binary);
	if (!ofile.good()) {
		std::cout << "Cannot open settings file for writing!" << std::endl;
		return false;
	}
	ofile.write((const char*)&settings, sizeof(settings));
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
	ifile.read((char*)&settings, sizeof(settings));
	ifile.close();
	return true;
}

