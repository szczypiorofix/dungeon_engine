/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <iostream>
#include <fstream>

#include "DungeonEngine.h"
#include "Defines.h"



DungeonEngine::DungeonEngine() {
	
	if (!readConfigFile()) {
		settings = {
		800,					// Screen width
		600,					// Screen height
		DungeonEngine::MIN_SCALE,		// scale
		0,// fullscreen
		10 // music volume
		};
	}	
	
	this->started = false;
	this->quit = false;
	this->window = NULL;
	this->glContext = NULL;
	this->currentMusic = NULL;
	this->camera = NULL;
	this->tilesOnScreenFromCenterX = 0;
	this->tilesOnScreenFromCenterY = 0;

	this->viewLockedOn = ViewLockedOn::PLAYER;

	this->scale = settings.scale;
	
	this->scrollVector = NULL;

}


DungeonEngine::~DungeonEngine() {
}


void DungeonEngine::initTimer() {
	//this->lastTime = SDL_GetTicks();
	//this->timer = SDL_GetTicks();
}


void DungeonEngine::initSDL(void) {
#ifdef _DEBUG 
	std::cout << "Initializing SDL audio & video main modules... ";
#endif
	this->started = (SDL_Init(SDL_INIT_VIDEO) == 0); // (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0);
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


void DungeonEngine::createWindow(void) {
#ifdef _DEBUG 
	std::cout << "Initializing SDL window... ";
#endif
	this->window = SDL_CreateWindow("Dungeon Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (this->window == NULL) {
		std::cout << "SDL_CreateWindow() error: " << SDL_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;
#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
}


void DungeonEngine::initOGL(void) {
#ifdef _DEBUG 
	std::cout << "Initializing OpenGL ... ";
#endif

	this->glContext = SDL_GL_CreateContext(this->window);
	if (this->glContext == NULL) {
		std::cout << "SDL_GL_CreateContext() error: " << SDL_GetError() << std::endl;
		this->started = false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1); // 1 - VSYNC ON, 0 - VSYNC OFF, -1 - adaptive VSYNC

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Spacify clear color
	glClearColor(0, 0, 0, 1);

	// Viewport to display
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Shader model
	glShadeModel(GL_SMOOTH); // GL_SMOOTH or GL_FLAT

	// 2D rendering
	glMatrixMode(GL_PROJECTION);

	// Save it!
	glLoadIdentity();

	// Disable depth checking
	glDisable(GL_DEPTH_TEST);

	

#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
}


void DungeonEngine::initializePngImages(void) {
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


void DungeonEngine::initializeAudioSystem(void) {
#ifdef _DEBUG 
	std::cout << "Initializing BASS audio module... ";
#endif
	if (BASS_Init(-1, 44100, 0, 0, NULL) < 0) {
		std::cout << "SDL_mixer BASS_Init() error code: " << BASS_ErrorGetCode() << std::endl;
		this->started = false;
	} else
		this->started = true;

	BASS_Start();

#ifdef _DEBUG
	std::cout << "done." << std::endl;
#endif
}


//void DungeonEngine::initializeNetworkSystem(void) {
//#ifdef _DEBUG 
//	std::cout << "Initializing SDL network module... ";
//#endif
//	if (SDLNet_Init() == -1) {
//		std::cout << "SDLNet_Init() error: " << SDLNet_GetError() << std::endl;
//		this->started = false;
//	} else
//		this->started = true;
//#ifdef _DEBUG
//	std::cout << "done." << std::endl;
//#endif

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

	
//}


void DungeonEngine::stop(void) {

	writeConfigFile();
#ifdef _DEBUG 
	std::cout << "Shutting down SDL modules..." << std::endl;
#endif

	SDL_FreeCursor(this->cursor);

	GraphicAssets::releaseAssets();

	delete this->currentMusic;

	SDL_GL_DeleteContext(this->glContext);
	SDL_DestroyWindow(this->window);

	//SDLNet_Quit();
	IMG_Quit();
	SDL_Quit();

#ifdef _DEBUG 
	std::cout << "All systems clear." << std::endl;
#endif
}


void DungeonEngine::launchSubsystems(void) {

	initSDL();
	createWindow();
	initOGL();
	initializePngImages();
	initializeAudioSystem();

	std::string cursorFileName = DIR_RES_IMAGES;
	cursorFileName.append("mouse_cursor.png");
	
	int m = SDL_SetRelativeMouseMode(SDL_FALSE); // Trap mouse on window
	if (m == -1) {
		std::cout << "Error while locking mouse pointer to the window." << std::endl;
		exit(1);
	}

	SDL_ShowCursor(SDL_ENABLE);
	SDL_WarpMouseInWindow(this->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


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


bool DungeonEngine::loadMusic(std::string musicFile) {
	currentMusic = new Music(musicFile);
	return true;
}


bool DungeonEngine::playMusic(bool loop, float volume) {
	this->currentMusic->playMusic(volume);
	return true;
}


bool DungeonEngine::isQuit(void) {
	return this->quit;
}


void DungeonEngine::setQuit(bool q) {
	this->quit = q;
}


SDL_Window* DungeonEngine::getWindow(void) {
	return this->window;
}


bool DungeonEngine::writeConfigFile(void) {
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


bool DungeonEngine::readConfigFile(void) {
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


void DungeonEngine::loadImageToAssets(std::string fileName, int spriteWidth, int spriteHeight, int imagesEnum) {
	//GraphicAssets::getAssets()->loadAsset(fileName, this->renderer, spriteWidth, spriteHeight, imagesEnum);
}


void DungeonEngine::drawImage(const int SpriteSheetNo, SDL_Rect clip, int x, int y) {
	//GraphicAssets::getAssets()->spriteSheets[SpriteSheetNo]->draw(
	//	this->renderer,
	//	&clip,
	//	x,
	//	y,
	//	this->scale);
}

GLuint DungeonEngine::loadTexture(const std::string& fileName) {
	std::string fn = DIR_RES_IMAGES + fileName;
	SDL_Surface* image = IMG_Load(fn.c_str());
	if (image == NULL) {
		std::cout << "Unable to load image " << fileName << ", : " << IMG_GetError() << std::endl;
		exit(1);
	}
	unsigned object(0);

	glGenTextures(1, &object);
	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	SDL_FreeSurface(image);

	return object;
}

