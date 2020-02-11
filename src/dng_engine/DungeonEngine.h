/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _DUNGEONENGINE_H_
#define _DUNGEONENGINE_H_
#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

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
	int musicVolume;
} Settings;


class DungeonEngine {

public:
	DungeonEngine();
	~DungeonEngine();

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static const int MIN_SCALE = 1;
	static const int MAX_SCALE = 5;

	const char* CONFIG_FILE_NAME = "dungeon_engine.cfg";

	void launchSubsystems(void);
	void stop(void);

	Settings settings;
	float scale;

	bool isQuit(void);
	void setQuit(bool quit);

	SDL_Cursor* cursor;
	SDL_Window* getWindow(void);
	
	void loadImageToAssets(std::string fileName, int spriteWidth, int spriteHeight, int imagesEnum);
	void drawImage(const int SpriteSheetNo, SDL_Rect clip, int x, int y);

	void initTimer(void);

	bool loadMusic(std::string musicFile);
	bool playMusic(bool loop, float volume);

	GLuint loadTexture(const std::string& fileName);

protected:
	SDL_Window* window;
	SDL_GLContext glContext;

	Camera* camera;

	Vector2* scrollVector;

	ViewLockedOn viewLockedOn;

private:

	Music* currentMusic;

	bool started;
	bool quit;
	int tilesOnScreenFromCenterX;
	int tilesOnScreenFromCenterY;

	bool writeConfigFile(void);
	bool readConfigFile(void);

	void initSDL(void);
	void createWindow(void);
	void initOGL(void);
	void initializePngImages(void);
	void initializeAudioSystem(void);

};

#endif
