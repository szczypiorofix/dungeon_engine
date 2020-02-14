/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <iostream>
#include <fstream>
#include <IL/il.h>

#include "DungeonEngine.h"
#include "Defines.h"



DungeonEngine::DungeonEngine() {
	
	this->cursor = NULL;
	this->scrollVector = NULL;
	
	this->settings = {
		800,							// Screen width
		600,							// Screen height
		DungeonEngine::MIN_SCALE,		// scale
		0,								// 1 - fullscreen, 0 - window
		0.5f							// music volume
	};	
	
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
	
	//this->scrollVector = NULL;

}


DungeonEngine::~DungeonEngine() {}


void DungeonEngine::initSDL(void) {
#ifdef _DEBUG 
	std::cout << "Initializing SDL audio & video main modules... \n";
#endif
	this->started = (SDL_Init(SDL_INIT_VIDEO) == 0); // (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0);
	if (!this->started) {
		std::cout << "SDL_Init() error : " << SDL_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;

	atexit(SDL_Quit);
}


void DungeonEngine::createWindow(void) {
#ifdef _DEBUG 
	std::cout << "Initializing SDL window... \n";
#endif
	this->window = SDL_CreateWindow("Dungeon Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (this->window == NULL) {
		std::cout << "SDL_CreateWindow() error: " << SDL_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;

}


void DungeonEngine::initOGL(void) {
#ifdef _DEBUG 
	std::cout << "Initializing OpenGL ... \n";
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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	// Setting OpenGL version to 3.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << std::endl;
	}

	if (SDL_GL_SetSwapInterval(1) < 0) { // 1 - VSYNC ON, 0 - VSYNC OFF, -1 - adaptive VSYNC
		std::cout <<  "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
	}

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

}





void DungeonEngine::initializePngImages(void) {
#ifdef _DEBUG 
	std::cout << "Initializing SDL PNG images module... \n";
#endif
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image IMG_Init() error: " << IMG_GetError() << std::endl;
		this->started = false;
	} else
		this->started = true;

}


void DungeonEngine::initializeAudioSystem(void) {
#ifdef _DEBUG 
	std::cout << "Initializing BASS audio module... \n";
#endif
	if (BASS_Init(-1, 44100, 0, 0, NULL) < 0) {
		std::cout << "SDL_mixer BASS_Init() error code: " << BASS_ErrorGetCode() << std::endl;
		this->started = false;
	} else
		this->started = true;

	BASS_Start();

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

	this->initSDL();
	
	// LOGGING SYSTEM
	//SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
	//SDL_LogError(SDL_LOG_PRIORITY_INFO, "SDL Logging system has started.");
	// LOGGING SYSTEM
	
	this->createWindow();
	this->initOGL();
	this->initializePngImages();
	this->initializeAudioSystem();




	// https://www.geeks3d.com/20090105/tutorial-how-to-load-and-display-an-image-with-devil-and-opengl/

	// https://moddb.fandom.com/wiki/DevIL:Tutorials:Basics
	ILuint texid; /* ILuint is a 32bit unsigned integer.
  Variable texid will be used to store image name. */
	ILboolean success; /* ILboolean is type similar to GLboolean and can equal GL_FALSE (0) or GL_TRUE (1)
	  it can have different value (because it's just typedef of unsigned char), but this sould be
	  avoided.
	  Variable success will be used to determine if some function returned success or failure. */
	GLuint image;
	int finished;

	ilInit(); /* Initialization of DevIL */
	ilGenImages(1, &texid); /* Generation of one image name */
	ilBindImage(texid); /* Binding of image name */
	std::string testImageFileName = DIR_RES_IMAGES;
	testImageFileName.append("logo-title.png");
	success = ilLoadImage(testImageFileName.c_str()); /* Loading of image "image.jpg" */
	if (success) /* If no error occured: */
	{
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into
		  unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
		if (!success)
		{
			/* Error occured */
			SDL_Quit();
		}
		glGenTextures(1, &image); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, image); /* Binding of texture name */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear
		  interpolation for magnification filter */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear
		  interpolation for minifying filter */
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
			ilGetData()); /* Texture specification */
	}
	else
	{
		/* Error occured */
		SDL_Quit();
	}
	ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data
	  we can release memory used by image. */





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


void DungeonEngine::loadMusic(std::string musicFile) {
	currentMusic = new Music(musicFile, 1.0f, true);
}


bool DungeonEngine::playMusic(float volume) {
	this->settings.musicVolume = volume;
	return this->currentMusic->playMusic(volume);
}


bool DungeonEngine::playMusic(void) {
	return this->currentMusic->playMusic(this->settings.musicVolume);
}


bool DungeonEngine::stopMusic(void) {
	return this->currentMusic->stopMusic();
}


bool DungeonEngine::pauseMusic(void) {
	return this->currentMusic->pauseMusic();
}


void DungeonEngine::releaseMusic(void) {
	delete this->currentMusic;
}


bool DungeonEngine::isQuit(void) {
	return this->quit;
}


void DungeonEngine::setQuit(bool q) {
	this->quit = q;
}


Music* DungeonEngine::getCurrentMusic(void) {
	return this->currentMusic;
}


SDL_Window* DungeonEngine::getWindow(void) {
	return this->window;
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

