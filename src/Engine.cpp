/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

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
		10 // music volume
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
#ifdef _DEBUG 
	std::cout << "Initializing SDL audio & video main modules... ";
#endif
	this->started = (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)  == 0);
	if (!this->started) {
		std::cout << "SDL_Init() error : " << SDL_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
	atexit(SDL_Quit);
}

void Engine::createWindow() {
#ifdef _DEBUG 
	std::cout << "Initializing SDL window... ";
#endif
	this->window = SDL_CreateWindow("Dungeon Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (this->window == NULL) {
		std::cout << "SDL_CreateWindow() error: " << SDL_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
}

void Engine::createRenderer() {
#ifdef _DEBUG 
	std::cout << "Initializing SDL renderer... ";
#endif
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer == NULL) {
		std::cout << "SDL_CreateRenderer() error: " << SDL_GetError() << std::endl;
		this->started = false;
	} else {
		SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
		this->started = true;
	}
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
}

void Engine::initializePngImages() {
#ifdef _DEBUG 
	std::cout << "Initializing SDL PNG images module... ";
#endif
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image IMG_Init() error: " << IMG_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
}

void Engine::initializeAudioSystem() {
#ifdef _DEBUG 
	std::cout << "Initializing SDL audio module... ";
#endif
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer Mix_OpenAudio() error: " << Mix_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
}

void Engine::initializeNetworkSystem() {
#ifdef _DEBUG 
	std::cout << "Initializing SDL network module... ";
#endif
	if (SDLNet_Init() == -1) {
		std::cout << "SDLNet_Init() error: " << SDLNet_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif

	//Uint16 port = 80;

	//IPaddress ip;
	//TCPsocket sd;
	//int quit, len; char buffer[512];

	//if (SDLNet_ResolveHost(&ip, "127.0.0.1", port) < 0) {
	//	fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE);
	//}

	///* Open a connection with the IP provided (listen on the host's port) */
	//if (!(sd = SDLNet_TCP_Open(&ip))) {
	//	fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE);
	//}

	//quit = 0; while (!quit) {
	//printf("Write something:\n>");
	//scanf_s("%s", buffer);

	//len = strlen(buffer) + 1;
	//if (SDLNet_TCP_Send(sd, (void*)buffer, len) < len) {
	//	fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE);
	//}

	//if (strcmp(buffer, "exit") == 0)
	//	quit = 1;
	//if (strcmp(buffer, "quit") == 0)
	//	quit = 1;
	//}

	//SDLNet_TCP_Close(sd);

	
}

void Engine::stop(void) {

	writeConfigFile();
#ifdef _DEBUG 
	std::cout << "Shutting down SDL modules... ";
#endif

	Mix_FreeMusic(this->music);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	//SDLNet_Quit();
	IMG_Quit();
	SDL_Quit();
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
}

void Engine::launchSubsystems(void) {

	initSDL();
	createWindow();
	createRenderer();
	initializePngImages();
	initializeAudioSystem();
	initializeNetworkSystem();

	std::string cursorFileName = DIR_RES_IMAGES;
	cursorFileName.append("mouse_cursor.png");
	
	SDL_Surface* cursorIcon = IMG_Load(cursorFileName.c_str());
	if (cursorIcon == NULL) {
		std::cout << "Unable to load image " << cursorFileName << ". SDL_image error: " << IMG_GetError() << std::endl;
		exit(1);
	} else {
		this->cursor = SDL_CreateColorCursor(cursorIcon, 0, 0);
		if (this->cursor == NULL) {
			std::cout << "Unable to create a mouse cursor !" << std::endl;
			exit(1);
		} else {
			SDL_SetCursor(this->cursor);
		}
	}

	

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
#ifdef _DEBUG 
	std::cout << "Saving config file... ";
#endif
	this->settings.scale = this->scale;

	std::ofstream ofile(CONFIG_FILE_NAME, std::ios::binary);
	if (!ofile.good()) {
		std::cout << "Cannot open settings file for writing!" << std::endl;
		return false;
	}
	ofile.write((const char*)&this->settings, sizeof(this->settings));
	ofile.close();
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
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

