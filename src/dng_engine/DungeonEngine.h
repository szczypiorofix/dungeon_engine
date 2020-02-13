/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _DUNGEONENGINE_H_
#define _DUNGEONENGINE_H_
#pragma once



#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Music.h"
#include "GraphicAssets.h"
#include "Camera.h"
#include "Vector2.h"


enum class ViewLockedOn {
	PLAYER,
	MOUSE
};


typedef struct Settings {
	int screenWidth;
	int screenHeight;
	float scale;
	int fullScreen;
	float musicVolume;
} Settings;


class DungeonEngine {

public:
	DungeonEngine();
	~DungeonEngine();

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static const int MIN_SCALE = 1;
	static const int MAX_SCALE = 5;

	void launchSubsystems(void);
	void stop(void);

	Settings settings;
	float scale;

	bool isQuit(void);
	void setQuit(bool quit);

	SDL_Cursor* cursor;
	SDL_Window* getWindow(void);

	void loadMusic(std::string musicFile);
	bool playMusic(float volume);
	bool playMusic(void);

	bool stopMusic(void);

	bool pauseMusic(void);

	void releaseMusic(void);

	GLuint loadTexture(const std::string& fileName);

	Music* getCurrentMusic(void);

protected:
	SDL_Window* window;
	SDL_GLContext glContext;

	Camera* camera;

	Vector2* scrollVector;

	ViewLockedOn viewLockedOn;


private:

	Music* currentMusic;

	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;

	bool started;
	bool quit;
	int tilesOnScreenFromCenterX;
	int tilesOnScreenFromCenterY;

	void initSDL(void);
	void createWindow(void);
	void initOGL(void);
	bool initShaders(void);
	void initializePngImages(void);
	void initializeAudioSystem(void);

};

#endif
